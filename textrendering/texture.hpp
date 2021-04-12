#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/glew.h>

GLuint initializeTexture(const unsigned char *image_data, int width, int height, GLenum format);
void updateTexture(const unsigned char *image_data, int width, int height, GLenum format);
GLuint loadImageToTexture(const char * imagePath);

#endif