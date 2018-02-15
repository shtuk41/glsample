#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.hpp"



GLFWwindow * window;

int main(int argc, char **argv)
{
	if (!glfwInit())
	{

		std::cout << "Failed to initialize GLFW\n" << std::endl;
		return (EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640,480, "Chapter 4 - GLSL", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.  Try the 2.1 version of the tutorials." << std::endl;

		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	GLuint program = LoadShaders("simple.vert","simple.frag");
	glBindFragDataLocation(program, 0,"color_out");
	glUseProgram(program);

	GLuint vertex_buffer;
	GLuint color_buffer;
	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &color_buffer);

	const GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	const GLfloat colors[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLint position_attrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(position_attrib);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0,(void*)0);

	GLint color_attrib = glGetAttribLocation(program, "color_in");
	glEnableVertexAttribArray(color_attrib);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);



	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES,0,6);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDisableVertexAttribArray(position_attrib);
	glDisableVertexAttribArray(color_attrib);
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &color_buffer);
	glDeleteVertexArrays(1, &vertex_array);
	glDeleteProgram(program);
	glfwDestroyWindow(window);
	glfwTerminate();




	std::cout << "Success. Exit" << std::endl;

	exit(EXIT_SUCCESS);
}