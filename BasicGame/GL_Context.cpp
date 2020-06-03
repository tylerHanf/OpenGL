#include "GL_Context.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Window.h"
#include "Error.h"
#include "../Utils/Utils.h"

GL_Context::GL_Context() { 
    if (!GL_init()) {
        Error().reportError("Failed to make GL_Context");
        exit(EXIT_FAILURE);
    }

    make_context();
}

GL_Context::~GL_Context() {
    glfwTerminate();
}

bool GL_Context::make_context() {
    numVAOs = 0;
    numVBOs = 0;
    rendereringProgram = createShaderProgram(VERTSHADER_PATH.c_str(), FRAGSHADER_PATH.c_str());
}

bool GL_Context::GL_init() {
    if (!glfwInit()) { Error().reportError("Failed to init glfw"); }    
    window = Window(SCREENWIDTH, SCREENHEIGHT, TITLE);
    glfwMakeContextCurrent(window.getWindow());
    if (glewInit() != GLEW_OK) { Error().reportError("Failed to init glew"); }
    glfwSwapInterval(1);
}