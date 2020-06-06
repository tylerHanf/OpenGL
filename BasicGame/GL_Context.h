#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ObjectData.h"
#include "Window.h"
#include "LoadData.h"
#include "Texture.h"
#include "Camera.h"
#include <vector>

class GL_Context {

    int numVAOs = 1;
    int numVBOs = 2;
    GLuint vao[1];
    GLuint vbo[2];


    GLuint renderingProgram;
    GLuint mvLoc, projLoc;
    glm::mat4 pMat, mMat, vMat, mvMat;

    GLFWwindow* window;
    int width, height = 800;
    float aspect;
    Camera *camera;

    //TESTING
    unsigned char* img;
    int imgWidth, imgHeight;
    GLuint rockTex;

    public:
        GL_Context(LoadData *ld);
        ~GL_Context();
        GLFWwindow* getWindow();
        //Load texture to gpu
        void loadTexToGPU(std::vector<Texture*> *textures, std::vector<GLuint> *textIDs);
        void loadVertsToGPU(std::vector<std::vector<float>> *verts, std::vector<std::vector<float>> *texels, std::vector<int> *vertIDs);
        GLuint* getVAO();
        GLuint* getVBO();
        void init();
        bool renderLoop(ObjectData objData);
        void display(ObjectData objData);
        void testSetup();
        void testTextLoad();

};

#endif