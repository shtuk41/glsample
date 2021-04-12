/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   texture2dobject.h
 * Author: aleksander
 *
 * Created on December 25, 2020, 6:38 AM
 */

#ifndef TEXTURE2DOBJECT_H
#define TEXTURE2DOBJECT_H

#include <texture.h>

float aspect_ratio = 3.0f/2.0f;
float z_offset =0.0f;

static const GLfloat g_vertex_buffer_data[] = 
{
        -aspect_ratio,-1.0f,z_offset,
        aspect_ratio,-1.0f,z_offset,
        aspect_ratio,1.0f,z_offset,
        -aspect_ratio,-1.0f,z_offset,
        aspect_ratio,1.0f,z_offset,
        -aspect_ratio,1.0f,z_offset,

};


static const GLfloat g_uv_buffer_data[] = 

{
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f
};

class Texture2dOjbect :  public RenderObject
{
private:

    GLuint texture_id;
    GLuint program_id;
    GLuint vertex_buffer;
    GLuint uv_buffer;
    GLuint vertex_array_id;
    GLuint texture_sampler_id;
    GLuint matrix_id;
    GLint  attribute_vertex;
    GLint  attribute_uv;
    
    
public:

	Texture2dOjbect() 
	{
            program_id = LoadShaders("texture.vert","texture.frag");
            texture_id = loadImageToTexture("image1.bmp");
            
            texture_sampler_id = glGetUniformLocation(program_id, "textureSampler");
            matrix_id = glGetUniformLocation(program_id, "MVP");
	}

	~Texture2dOjbect()
	{
            glDisableVertexAttribArray(attribute_vertex);
            glDisableVertexAttribArray(attribute_uv);
            // Clean up VBO and shader
            glDeleteBuffers(1, &vertex_buffer);
            glDeleteBuffers(1, &uv_buffer);
            glDeleteProgram(program_id);
            glDeleteTextures(1, &texture_id);
            glDeleteVertexArrays(1, &vertex_array_id);
            // Close OpenGL window and terminate GLFW
	}
        
        void UseProgram()
        {
            glUseProgram(program_id);
        }

	void Setup()
	{
            glGenVertexArrays(1,&vertex_array_id);
            glBindVertexArray(vertex_array_id);
            
            
            glGenBuffers(1,&vertex_buffer);
            glGenBuffers(1,&uv_buffer);
            
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
            attribute_vertex = glGetAttribLocation(program_id, "vertexPosition_modelspace");
            glVertexAttribPointer(attribute_vertex,3,GL_FLOAT, GL_FALSE,0,(void*)0);
            glEnableVertexAttribArray(attribute_vertex);
            
            
            glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
            attribute_uv = glGetAttribLocation(program_id,"vertexUV");
            glVertexAttribPointer(attribute_uv, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(attribute_uv);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_id);
          
	}
        
        virtual void Draw()
	{
            
	}   
        
        void Draw(glm::mat4 &mvp)
	{
            glBindVertexArray(vertex_array_id);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            
            glUniform1i(texture_sampler_id, 0);
            
            glUniformMatrix4fv(matrix_id,1,GL_FALSE, &mvp[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, 6);
	}    
};



#endif /* TEXTURE2DOBJECT_H */

