/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   axis.h
 * Author: aleksander
 *
 * Created on December 13, 2019, 9:48 PM
 */

#ifndef AXES3D_H
#define AXES3D_H

#include <render_object.h>

class Axes3d : public RenderObject
{
private:

	GLuint vertex_array_id;
	GLuint vertex_buffer[2];
	GLint position_attribute;
	GLint color_attribute;
        
        float xLength, yLength, zLength;
    
public:

	Axes3d(float x, float y, float z) : xLength(x), yLength(y), zLength(z)
	{

	}

	~Axes3d()
	{
            glDeleteBuffers(2, vertex_buffer);
            glDeleteVertexArrays(1, &vertex_array_id);
            glDisableVertexAttribArray(position_attribute);
            glDisableVertexAttribArray(color_attribute);
	}

	void Setup(GLuint program_id)
	{
            glGenVertexArrays(1, &vertex_array_id);
    
            glBindVertexArray(vertex_array_id);

            GLfloat axis_lines[] = {
                                        0.0f,0.0f,0.0f,
                                        1.0f * xLength,0.0f,0.0f,
                                        0.0f,0.0f,0.0f,
                                        0.0f,1.0f * yLength,0.0f,
                                        0.0f,0.0f,0.0f,
                                        0.0f,0.0f,1.0f * zLength
                                    };
                
            GLfloat axis_colors[] = {
                                        1.0f,0.0f,0.0f,
                                        1.0f,0.0f,0.0f,
                                        0.0f,1.0f,0.0f,
                                        0.0f,1.0f,0.0f,
                                        0.0f,0.0f,1.0f,
                                        0.0f,0.0f,1.0f
                                    };
            
            glGenBuffers(2,vertex_buffer);

            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(axis_lines), axis_lines, GL_STATIC_DRAW);
            position_attribute = glGetAttribLocation(program_id, "vPosition");
            glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(position_attribute);

            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[1]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(axis_colors), axis_colors, GL_STATIC_DRAW);
            color_attribute = glGetAttribLocation(program_id, "vColor");
            glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(color_attribute);
	}
        
        virtual void Draw()
	{
            glBindVertexArray(vertex_array_id);
            glDrawArrays(GL_LINES, 0, 6);
	}
};

#endif /* AXES3D_H */

