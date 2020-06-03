#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

class GL_Context {
    const int SCREENWIDTH = 800;
    const int SCREENHEIGHT = 800;
    const std::string TITLE = "SPHERE GAME";
    const std::string VERTSHADER_PATH = "vertShader.glsl";
    const std::string FRAGSHADER_PATH = "fragShader.glsl";

    int numVAOs;
    int numVBOs;

    GLuint rendereringProgram;
    GLuint mvLoc, projLoc;

    Window window;

    bool make_context();
    bool GL_init();

    public:
        GL_Context();
        ~GL_Context();
};

#endif