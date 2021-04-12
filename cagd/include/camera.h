/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camera.h
 * Author: aleksander
 *
 * Created on December 11, 2019, 10:56 PM
 */

#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
private:
    glm::vec3 g_position;   
    float speed;
    float g_initial_fov;
    glm::mat4 g_view_matrix;
    glm::mat4 g_projection_matrix;
    GLFWwindow * window;
    
public:
    Camera(GLFWwindow * w, float speed = 3.0f) : speed(speed), window(w)
    {
        g_position = glm::vec3(0,0,5);
        g_initial_fov = glm::pi<float>() * 0.25f;
    }
    
    glm::mat4 getViewMatrix() const
    {
        return g_view_matrix;
    }
    
    glm::mat4 getProjectionMatrix() const
    {
        return g_projection_matrix;
    }
    
    glm::vec3 getPosition() const
    {
        return g_position;
    }
    
    void computeViewProjectionMatrices(bool moveback, bool moveforward)
    {
	static double last_time = glfwGetTime();

	double current_time = glfwGetTime();
	float delta_time = float(current_time - last_time);
	
        int width, height;
	glfwGetWindowSize(window, &width, &height);
	//direction vector for movement
	glm::vec3 direction(0,0,-1);
	//up vector
	glm::vec3 up = glm::vec3(0,1,0);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || moveback)
	{
            float extraspeed = (moveback ? 5.0f : 1.0f);
            
            g_position += direction *delta_time * speed * extraspeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || moveforward)
	{
            float extraspeed = (moveforward ? 5.0f : 1.0f);
            
            g_position -= direction *delta_time * speed * extraspeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		g_initial_fov -= 0.1 * delta_time * speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		g_initial_fov += 0.1 * delta_time * speed;
	}

	/*update projection matrix: Field of View, aspect ratio, display range : 0.1 unit <-> 100 units */
	g_projection_matrix = glm::perspective(g_initial_fov, (float)width/(float)height, 0.1f, 10.0f);

	//update the view matrix
	g_view_matrix = glm::lookAt(g_position, g_position + direction, up);
	last_time = current_time;
    }
};


#endif /* CAMERA_H */

