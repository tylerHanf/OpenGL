#ifndef UTILS_H
#define UTILS_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <string>

//Shader error
void printShaderLog(GLuint shader);

//Program Error
void printProgramLog(int prog);

//Determines if error
bool checkOpenGLError();

//Read in GLSL file
std::string readShaderSource(const char *filePath);

//Make shader program with just vertex and frag shader
GLuint createShaderProgram(const char *vp, const char *fp);

//Load image texture
GLuint loadTexture(const char* textImagePath);

void getPNGDim(std::string filepath, int *width, int *height);
//GLuint createShaderProgram(const char *vp, const char *gp, const char *fp){}
//GLuint createShaderProgram(const char *vp, const char *tCS, const char* tES, const char *fp){}
//GLuint createShaderProgram(const char *vp, const char *tCS, const char* tES, const char *gp, const char *fp){}

#endif
