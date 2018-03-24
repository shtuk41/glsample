#ifndef _CONTROLS_H
#define _CONTROLS_H

#include <GLFW/glfw3.h>


glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void computeViewProjectionMatrices(GLFWwindow * window);

#endif