/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   texture.h
 * Author: aleksander
 *
 * Created on December 11, 2019, 10:27 PM
 */

#ifndef TEXTURE_H
#define TEXTURE_H

GLuint initializeTexture(const unsigned char *image_data, int width, int height, GLenum format);
void updateTexture(const unsigned char *image_data, int width, int height, GLenum format);
GLuint loadImageToTexture(const char * imagePath);

#endif /* TEXTURE_H */

