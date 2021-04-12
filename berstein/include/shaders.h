/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   shaders.h
 * Author: aleksander
 *
 * Created on December 11, 2019, 10:26 PM
 */

#ifndef SHADERS_H
#define SHADERS_H

std::string readSourceFile(const char *path);
void CompileShader(std::string program_code, GLuint shader_id);
GLuint LoadShaders(const char * vertex_file_path, const char *fragment_file_path);



#endif /* SHADERS_H */

