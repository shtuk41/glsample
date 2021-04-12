/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   face.h
 * Author: aleksander
 *
 * Created on December 12, 2019, 9:57 PM
 */

#ifndef FREETYPEFACE_H
#define FREETYPEFACE_H

#include <GL/glew.h>
#include <exceptions.h>

#include <ft2build.h>
#include FT_FREETYPE_H

class FreeType
{
private:
    FT_Library ft_lib;
    GLuint texture, sampler;
    GLuint vbo, vao;
    GLuint  program;
    GLuint texUniform;   
    GLuint colorUniform;
    
    
protected:
    FT_Face face;
    
public:
    
    FreeType()
    {
        if(FT_Init_FreeType(&ft_lib) != 0) 
        {
            std::cerr << "Couldn't initialize FreeType library\n";
        
            throw new UnableToInitializeFreeTypeLibrary();
        }
        
        if(FT_New_Face(ft_lib, "/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 0, &face) != 0) 
        {
            std::cerr << "Unable to load font\n";
            
            throw new UnableToFindFontFile();
        }
        
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);
        glGenTextures(1, &texture);
        glGenSamplers(1, &sampler);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Initialize shader
        program = LoadShaders("freetype.vert","freetype.frag");
        glUseProgram(program);

        glUseProgram(program);
        glBindAttribLocation(program, 0, "in_Position");
        texUniform = glGetUniformLocation(program, "tex");
        colorUniform = glGetUniformLocation(program, "color");
        
    }
    
    ~FreeType()
    {
        glDeleteTextures(1, &texture);
        glDeleteSamplers(1, &sampler);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
        
        FT_Done_Face(face);
        FT_Done_FreeType(ft_lib);
    }
    
    void Draw()
    {
        glUseProgram(program);
         
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindSampler(0, sampler);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glUseProgram(program);
        glUniform4f(colorUniform, 1, 1, 0, 1);
        glUniform1i(texUniform, 0);
    }
};


class Readout : public virtual FreeType
{
private:
    double posX;
    double posY;
    int size;
    
    void render_text(const std::string &str, FT_Face face, float x, float y, float sx, float sy) 
    {
        FreeType::Draw();
        
         FT_Set_Pixel_Sizes(face, 0, size);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        const FT_GlyphSlot glyph = face->glyph;

        for(unsigned int ii = 0; ii < str.length(); ii++) {
            if(FT_Load_Char(face, str[ii], FT_LOAD_RENDER) != 0)
                continue;

            glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
                         glyph->bitmap.width, glyph->bitmap.rows,
                         0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

            const float vx = x + glyph->bitmap_left * sx;
            const float vy = y + glyph->bitmap_top * sy;
            const float w = glyph->bitmap.width * sx;
            const float h = glyph->bitmap.rows * sy;

            struct {
                float x, y, s, t;
            } data[6] = {
                {vx    , vy    , 0, 0},
                {vx    , vy - h, 0, 1},
                {vx + w, vy    , 1, 0},
                {vx + w, vy    , 1, 0},
                {vx    , vy - h, 0, 1},
                {vx + w, vy - h, 1, 1}
            };

            glBufferData(GL_ARRAY_BUFFER, 24*sizeof(float), data, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (glyph->advance.x >> 6) * sx;
            y += (glyph->advance.y >> 6) * sy;
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    }
    
    
public:
    Readout(double x, double y, int size) : posX(x), posY(y), size(size)
    {
        
    }
    
    void Draw(const std::string &str, float sx, float sy)
    {
        render_text(str, face, posX, posY, sx, sy) ;
    }
    
    
};

#endif /* FREETYPEFACE_H */

