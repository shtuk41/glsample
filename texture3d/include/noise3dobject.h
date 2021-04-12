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

#ifndef TEXTURE3DOBJECT_H
#define TEXTURE3DOBJECT_H

#include <exception>
#include <iostream>

#include <texture.h>
#include <perlin.h>


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

class Texture3dObject :  public RenderObject
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
    
    int     imageCount;
    int     imageWidth;
    int     imageHeight;
    
    
public:

	Texture3dObject() 
	{
            //std::string path = "test.bmp";    
            std::string path = "grayscaletest.png";  
    
            std::ifstream check(path.c_str());

            if (check.good())
            {
                std::cout << "file exists" << std::endl;
            }
            else
            {

                std::cout << "cannot find file" << std::endl;
            }

                      
           
            program_id = LoadShaders("texture3.vert","texture3.frag");
            
            imageCount = 100;
            imageHeight = 100;
            imageWidth = 100;
            
            size_t bufferSize = imageCount * imageWidth*imageHeight;
            
            char* chBuffer = new char[ bufferSize ];
            
            unsigned int index = 0;
            
            for (int kk = 0; kk < imageCount; kk++)
            {
                for (int ii = imageHeight - 1; ii >= 0; ii--)
                {
                    for (int jj = 0; jj < imageWidth; jj++)
                    {
                        //if (jj < 1)
                        //std::cout << ii << " " << jj << " " <<  (int)mapFile.at<uchar>(jj, ii) << std::endl;
                         chBuffer[index] = (int)(255 * ((perlinNoise_2(ii,jj) + 1.0) / 2));
                        
                        index++;
                    }   
                }
            }
            
            std::cout << "index: " << index << std::endl; 
            
          
            char* pRGBABuffer = new char[ imageCount*imageWidth*imageHeight*4 ];
            
            
            for( int nIndx = 0; nIndx < imageCount*imageWidth*imageHeight; ++nIndx )
            {
                pRGBABuffer[nIndx*4] = chBuffer[nIndx];
                pRGBABuffer[nIndx*4+1] = chBuffer[nIndx];
                pRGBABuffer[nIndx*4+2] = chBuffer[nIndx];
                pRGBABuffer[nIndx*4+3] = chBuffer[nIndx];
            }
            
            glGenTextures(1,(GLuint*)&texture_id );
            
            glBindTexture( GL_TEXTURE_3D, texture_id );
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            
            //float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
            //glTexParameterfv(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, borderColor);  

            glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, imageWidth, imageHeight, imageCount, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, pRGBABuffer );
            glBindTexture( GL_TEXTURE_3D, 0 );
            
            
            
            texture_sampler_id = glGetUniformLocation(program_id, "textureSampler");
            matrix_id = glGetUniformLocation(program_id, "MVP");
            
             delete [] chBuffer;
             delete [] pRGBABuffer;
	}

	~Texture3dObject()
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
            
            float aspect_ratio = 3.0f/2.0f;
            float z_offset =0.0f;
            
            const int numberOfVertices = 1800;
            
            GLfloat g_vertex_buffer_data_3d[numberOfVertices];
            
            for (int ii = 0; ii < numberOfVertices; ii+=18)
            {
                g_vertex_buffer_data_3d[ii] = -aspect_ratio;
                g_vertex_buffer_data_3d[ii + 1] =  -1.0f; 
                g_vertex_buffer_data_3d[ii + 2] =  z_offset; 
                g_vertex_buffer_data_3d[ii + 3] =  aspect_ratio ;
                g_vertex_buffer_data_3d[ii + 4] =  -1.0f;
                g_vertex_buffer_data_3d[ii + 5] =  z_offset;
                g_vertex_buffer_data_3d[ii + 6] =  aspect_ratio;
                g_vertex_buffer_data_3d[ii + 7] =  1.0f;
                g_vertex_buffer_data_3d[ii + 8] =  z_offset;
                g_vertex_buffer_data_3d[ii + 9] =  -aspect_ratio;
                g_vertex_buffer_data_3d[ii + 10] =  -1.0f;
                g_vertex_buffer_data_3d[ii + 11] = z_offset;
                g_vertex_buffer_data_3d[ii + 12] = aspect_ratio;
                g_vertex_buffer_data_3d[ii + 13] = 1.0f;
                g_vertex_buffer_data_3d[ii + 14] = z_offset;
                g_vertex_buffer_data_3d[ii + 15] = -aspect_ratio;
                g_vertex_buffer_data_3d[ii + 16] = 1.0f;
                g_vertex_buffer_data_3d[ii + 17] = z_offset;
                        
                z_offset =    z_offset + 0.01f;     
            }
            
            GLfloat g_uv_buffer_data_3d[numberOfVertices];
            
            float zstep = 1.0f/100.0f;
            z_offset = 0.0;
            
            for (int ii = 0; ii < numberOfVertices; ii+=18)
            {
                g_uv_buffer_data_3d[ii] =  0.0f;
                g_uv_buffer_data_3d[ii+1] =  0.0f;
                g_uv_buffer_data_3d[ii+2] =  z_offset;
                g_uv_buffer_data_3d[ii+3] =  1.0f;
                g_uv_buffer_data_3d[ii+4] =  0.0f;
                g_uv_buffer_data_3d[ii+5] =  z_offset;
                g_uv_buffer_data_3d[ii+6] =  1.0f;
                g_uv_buffer_data_3d[ii+7] =  1.0f;
                g_uv_buffer_data_3d[ii+8] =  z_offset;
                g_uv_buffer_data_3d[ii+9] =  0.0f;
                g_uv_buffer_data_3d[ii+10] =  0.0f;
                g_uv_buffer_data_3d[ii+11] =  z_offset;
                g_uv_buffer_data_3d[ii+12] =  1.0f;
                g_uv_buffer_data_3d[ii+13] =  1.0f;
                g_uv_buffer_data_3d[ii+14] =  z_offset;
                g_uv_buffer_data_3d[ii+15] =  0.0f;
                g_uv_buffer_data_3d[ii+16] =  1.0f;
                g_uv_buffer_data_3d[ii+17] =  z_offset;
                        
                z_offset = z_offset + zstep;
            };
            
            /*
               
             */
            
            
            
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_3d), g_vertex_buffer_data_3d, GL_STATIC_DRAW);
            attribute_vertex = glGetAttribLocation(program_id, "vertexPosition_modelspace");
            glVertexAttribPointer(attribute_vertex,3,GL_FLOAT, GL_FALSE,0,(void*)0);
            glEnableVertexAttribArray(attribute_vertex);
            
            
            glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data_3d), g_uv_buffer_data_3d, GL_STATIC_DRAW);
            attribute_uv = glGetAttribLocation(program_id,"vertexUV");
            glVertexAttribPointer(attribute_uv, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(attribute_uv);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_3D, texture_id);
          
	}
        
        virtual void Draw()
	{

	}   
        
        void Draw(glm::mat4 &mvp)
	{
            glBindVertexArray(vertex_array_id);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_3D, texture_id);
            
            glUniform1i(texture_sampler_id, 0);
            
            glUniformMatrix4fv(matrix_id,1,GL_FALSE, &mvp[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, 6);
	}    
};



#endif /* TEXTURE2DOBJECT_H */

