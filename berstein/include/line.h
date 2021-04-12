/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   line.h
 * Author: aleksander
 *
 * Created on December 12, 2019, 9:20 PM
 */

#ifndef LINE_H
#define LINE_H

#include <render_object.h>


class Line : public RenderObject
{
public:

	Line(int numberOfPoints)
	{
		points = new Point[numberOfPoints];
		delta = 1.0 / (numberOfPoints - 1);
	}

	~Line()
	{
		glDisableVertexAttribArray(position_attribute);
		glDisableVertexAttribArray(color_attribute);
		glDeleteBuffers(2, vertex_buffer);
		glDeleteVertexArrays(1, &vertex_array_id);
		delete [] g_vertex_buffer_data;
		delete [] g_vertex_buffer_color;
		delete [] points;
	}

	void Setup(GLuint program_id, Point startPoint, Point endPoint)
	{
		double t = 0.0;

		for (int ii = 0; ii < 32; ii++)
		{
			points[ii] = startPoint * (1.0 - t) + endPoint * t;
		    t += delta;
		}

		//setup graphcis

		 glGenVertexArrays(1,&vertex_array_id);


		//b0_2
		glBindVertexArray(vertex_array_id);

		g_vertex_buffer_data = new GLfloat[32 * 3];
		g_vertex_buffer_color = new GLfloat[32 * 3];

		for (int ii = 0; ii < 32; ii++)
		{
			g_vertex_buffer_data[ii * 3] = points[ii].x;
			g_vertex_buffer_data[ii * 3 + 1] = points[ii].y;
			g_vertex_buffer_data[ii * 3 + 2] = points[ii].z;

			g_vertex_buffer_color[ii * 3] = 0.0f;
			g_vertex_buffer_color[ii * 3 + 1] = 0.0f;
			g_vertex_buffer_color[ii * 3 + 2] = 1.0f;


		}

		glGenBuffers(2,vertex_buffer);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[0]);
		glBufferData(GL_ARRAY_BUFFER, 32 * 3 * sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);
		position_attribute = glGetAttribLocation(program_id, "vPosition");
		glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(position_attribute);


		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[1]);
		glBufferData(GL_ARRAY_BUFFER, 32 * 3 * sizeof(GLfloat), g_vertex_buffer_color, GL_STATIC_DRAW);
		color_attribute = glGetAttribLocation(program_id, "vColor");
		glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(color_attribute);
	}
        
        virtual void Draw()
	{

		  glBindVertexArray(vertex_array_id);
		  glDrawArrays(GL_LINE_STRIP, 0, 32);
	}

	Point * GetPoints()
	{
		return points;
	}

private:

	double delta;
	Point * points;
	GLuint vertex_array_id;
	GLuint vertex_buffer[2];
	GLint position_attribute;
	GLint color_attribute;
	GLfloat *g_vertex_buffer_data;
	GLfloat *g_vertex_buffer_color;

};

#endif /* LINE_H */

