/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   curve.h
 * Author: aleksander
 *
 * Created on December 13, 2019, 11:06 PM
 */

#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <render_object.h>
#include <point.h>

class XCurve : RenderObject
{
private:

    GLuint vertex_array_id;
    GLuint vertex_buffer[2];
    GLint position_attribute;
    GLint color_attribute;
    GLfloat *g_vertex_buffer_data;
    GLfloat *g_vertex_buffer_color;
    int numberOfPoints;
    
public:
    
    XCurve(int numberOfpoints) : numberOfPoints(numberOfpoints)
    {
        g_vertex_buffer_data = new GLfloat[numberOfpoints * 3];
        g_vertex_buffer_color = new GLfloat[numberOfpoints * 3];
        
    }
    
    ~XCurve()
    {
        delete [] g_vertex_buffer_data;
        delete [] g_vertex_buffer_color;
        glDeleteBuffers(2, vertex_buffer);
        glDeleteVertexArrays(1, &vertex_array_id);
        
        
        glDisableVertexAttribArray(position_attribute);
        glDisableVertexAttribArray(color_attribute);
  
    }
    
    void Setup(GLuint program_id, Point points[])
    {
        for (int ii = 0; ii < 32; ii++)
        {
                g_vertex_buffer_data[ii * 3] = points[ii].x;
                g_vertex_buffer_data[ii * 3 + 1] = points[ii].y;
                g_vertex_buffer_data[ii * 3 + 2] = points[ii].z;

                g_vertex_buffer_color[ii * 3] = 1.0f;
                g_vertex_buffer_color[ii * 3 + 1] = 1.0f;
                g_vertex_buffer_color[ii * 3 + 2] = 1.0f;
        }
        
        
        glGenVertexArrays(1, &vertex_array_id);
    
        glBindVertexArray(vertex_array_id);
        glGenBuffers(2,vertex_buffer);

         glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[0]);
        glBufferData(GL_ARRAY_BUFFER, numberOfPoints * 3 * sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);
        GLint position_attribute = glGetAttribLocation(program_id, "vPosition");
        glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(position_attribute);


        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[1]);
        glBufferData(GL_ARRAY_BUFFER, numberOfPoints * 3 * sizeof(GLfloat), g_vertex_buffer_color, GL_STATIC_DRAW);
        GLint color_attribute = glGetAttribLocation(program_id, "vColor");
        glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(color_attribute);
    }
    
    
    virtual void Draw()
    {
        glBindVertexArray(vertex_array_id);
        glDrawArrays(GL_LINE_STRIP, 0, numberOfPoints);
    }
            
};


#endif /* CURVE_H */

