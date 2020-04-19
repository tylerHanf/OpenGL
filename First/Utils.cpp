#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Utils.h"

/*
 * Shader error log
 */
void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

/*
 * Program error log
 */
void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

/*
 * Determines if error
 */
bool checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

/*
 * Read in GLSL file
 */
std::string readShaderSource(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

/*
 * Makes shader program with vertex and fragment shader
 */
GLuint createShaderProgram(const char *vp, const char *fp) {

	//Vertex error
	GLint vertCompiled;
	//Fragment error
	GLint fragCompiled;
	//Linker error
	GLint linked;

	std::string vshaderSourceStr = readShaderSource(vp);
	std::string fshaderSourceStr = readShaderSource(fp);

	const char *vshaderSource = vshaderSourceStr.c_str();
	const char *fshaderSource = fshaderSourceStr.c_str();

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);

	//Compile vertex shader
	glCompileShader(vShader);

	//Check for vertex shader compilation error
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		std::cout << "vertex compilation failed" << std::endl;
		printShaderLog(vShader);
	}

	//Compile fragment shader
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		std::cout << "fragment compilation failed" << std::endl;
		printShaderLog(fShader);
	}

	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	//Link Errors
	checkOpenGLError();
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		std::cout << "Linking failed" << std::endl;
		printProgramLog(vfProgram);
	}
	return vfProgram;
}

//GLuint createShaderProgram(const char *vp, const char *gp, const char *fp){}
//GLuint createShaderProgram(const char *vp, const char *tCS, const char* tES, const char *fp){}
//GLuint createShaderProgram(const char *vp, const char *tCS, const char* tES, const char *gp, const char *fp){}
