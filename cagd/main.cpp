#define GLM_FORCE_RADIANS

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <sstream>

#include <vector>
#include <SOIL.h>
#include <exception>

using namespace glm;

#include <exceptions.h>
#include <shaders.h>
#include <camera.h>
#include <freetype.h>
#include <point.h>
#include <de_casteljau_bcurve.h>
#include <line.h>
#include <window.h>
#include <helpers.h>
#include <axes3d.h>
#include <xcurve.h>

float rotateY = 0.0f;
float rotateX = 0.0f;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
        if (action != GLFW_PRESS && action != GLFW_REPEAT)

                 return ;

        switch (key)

        {

        case GLFW_KEY_ESCAPE:

                 glfwSetWindowShouldClose(window, GL_TRUE);

                 break;

        case GLFW_KEY_SPACE:

                 rotateX = 0;

                 rotateY = 0;

                 break;

        case GLFW_KEY_Z:

                 rotateX+=0.01;

                 break;

        case GLFW_KEY_X:

                 rotateX-=0.01;

                 break;

        case GLFW_KEY_A:

                 rotateY+=0.01;

                 break;

        case GLFW_KEY_S:

                 rotateY-=0.01;

                 break;

        default:

                 break;

        }
}

double previous_xpos;
double previous_ypos;
double xposition;
double yposition;
bool rotateEnable = false;

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    xposition = xpos;
    yposition = ypos;
    
    if (rotateEnable)
    {    
        double delta_x = xpos - previous_xpos;
    
        rotateY+=(0.005 * delta_x);
        
        double delta_y = ypos - previous_ypos;

        rotateX+= (0.005 * delta_y);

        previous_xpos = xpos;
        previous_ypos = ypos;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            double xpos, ypos;
        
            glfwGetCursorPos(window, &xpos, &ypos);

            previous_xpos = xpos;
            previous_ypos = ypos;

            rotateEnable = true;
        }
        else if (action == GLFW_RELEASE)
        {
            rotateEnable = false;
        }
    }
}

bool moveback = false;
bool moveforward = false;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset >= 1.0)
    {
        moveback = true;
        moveforward = false;
    }
    else if (yoffset <= 1.0)
    {
        moveback = false;
        moveforward = true;
    }
 }

void mouse_instersections(Camera & cam)
{
    double x = (2.0 * xposition) / 640.0 - 1.0;
    double y = 1.0f - (2.0 * yposition) / 480.0;
    double z = -1.0f;
    
    std::cout << "init: " << x << " "  << y << " " << z << std::endl;
    
    glm::mat4 model_matrix = glm::mat4(1.0);


         model_matrix = glm::rotate(model_matrix, glm::pi<float>() * rotateY, glm::vec3(0.0f,1.0f,0.0f));
         model_matrix = glm::rotate(model_matrix, glm::pi<float>() * rotateX, glm::vec3(1.0f,0.0f,0.0f));

    
   
    vec4 newy = cam.getProjectionMatrix() * cam.getViewMatrix() * model_matrix * vec4(0.0,1,0,1);
    
    std::cout << "rnewy: " << newy.x /  newy.w << " " << newy.y / newy.w << " " << newy.z / newy.w << std::endl;
}

int main(int argc, char **argv)
{
    Window window(640,480,key_callback, mouse_callback, mouse_button_callback, scroll_callback);
       
    Camera camera(window.GetHandler());

    glewExperimental = true; // needed for core profile

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to Initialize GLEW" << std::endl;

        window.~Window();

        return 0;
    }

     //BLEND settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //CREATE PROGRAM
    GLuint program_id = LoadShaders("bezier.vert","bezier.frag");
    //glBindFragDataLocation(program_id, 1,"color_out");
    glUseProgram(program_id);


    //get the location for our "MPV" uniform variable 
    GLuint matrix_id = glGetUniformLocation(program_id, "MVP");

    //calc part

    Point b0 = Point(0,0,0);
    Point b1 = Point(0,0.5,0.5);
    Point b2 = Point(2,0.5,0.5);
    Point b3 = Point(2,0,0.7);
    Point b4 = Point(0,0,0);

    Line b0_b1(32);
    b0_b1.Setup(program_id,b0,b1);
    Line b1_b2(32);
    b1_b2.Setup(program_id,b1,b2);
    Line b2_b3(32);
    b2_b3.Setup(program_id,b2,b3);
    Line b3_b4(32);
    b3_b4.Setup(program_id,b3,b4);

    Point b0_2[32];

    std::vector<Point> points = {b0, b1, b2, b3, b4};
    
    de_Casteljau_BCurve curve(points, 32);
    
    for (int ii = 0; ii < 32; ii++)
    {
        b0_2[ii] = curve[ii];
    }
        
    XCurve deCasteljauCurve(32);
    deCasteljauCurve.Setup(program_id, b0_2);

    //axis
    Axes3d axes3d(1.0f,1.0f,1.0f);
    axes3d.Setup(program_id);
    
    //rendering text
    Readout readout(-1,0, 40);
    Readout readout2(-1,-0.2, 25);
    
    double test_double_increment = -99999;
    
    do
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         
         glUseProgram(program_id);

         //compute the MVP matrix from keyboard and mouse input
         camera.computeViewProjectionMatrices(moveback, moveforward);
         
         mouse_instersections(camera);
         
         moveback = false;
         moveforward = false;
         
         
         glm::mat4 projection_matrix = camera.getProjectionMatrix();
         glm::mat4 view_matrix = camera.getViewMatrix();
         glm::mat4 model_matrix = glm::mat4(1.0);


         model_matrix = glm::rotate(model_matrix, glm::pi<float>() * rotateY, glm::vec3(0.0f,1.0f,0.0f));
         model_matrix = glm::rotate(model_matrix, glm::pi<float>() * rotateX, glm::vec3(1.0f,0.0f,0.0f));

         glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

        //glm::mat4 mvp = mat4(1.0);

         glUniformMatrix4fv(matrix_id,1,GL_FALSE, &mvp[0][0]);

         axes3d.Draw();
         
         deCasteljauCurve.Draw();

         b0_b1.Draw();
         b1_b2.Draw();
         b2_b3.Draw();
         b3_b4.Draw();
         
        std::string rotate_y = to_string(rotateY);
        
        const double SCALEX = 2.0 / window.GetWidth();
        const double SCALEY = 2.0 / window.GetHeight();
        
        readout.Draw(rotate_y.c_str(), SCALEX, SCALEY);
        readout2.Draw(rotate_y.c_str(), SCALEX, SCALEY);
                        
        test_double_increment+=1.0;
        
         //swap buffers

        glfwSwapBuffers(window.GetHandler());
        glfwPollEvents();
    } //check if the ESC key was pressed or the window was closed
    while (!glfwWindowShouldClose(window.GetHandler()) &&
    	glfwGetKey(window.GetHandler(), GLFW_KEY_ESCAPE ) != GLFW_PRESS);
        
        
    glDeleteProgram(program_id);

    window.Destroy();
    window.~Window();

    return 0;

}
