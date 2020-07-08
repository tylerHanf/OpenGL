#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL2/SOIL2.h>
#include <string>
#include <vector>
#include "Window.h"
#include "Debug.h"
#include "Texture.h"
#include "Object.h"
#include "../Utils/Utils.h"
#include "LoadData.h"
#include "GL_Context.h"

GL_Context::GL_Context(LoadData *ld) :
camera()
{ 
    init();
    loadVertsToGPU(ld->getVertices(), ld->getTexels(), ld->getVertIDs());
    loadTexToGPU(ld->getTextures(), ld->getTextIDs());
}

GL_Context::~GL_Context() {
    glfwTerminate();
}

GLFWwindow* GL_Context::getWindow() {
    return window;
}

void GL_Context::loadTexToGPU(std::vector<Texture> &textures, std::vector<GLuint> &textIDs) {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(textures.size(), &textIDs[0]);
    for (int i=0; i<textures.size(); i++) {
        textIDs.push_back(textIDs.at(i));
        glBindTexture(GL_TEXTURE_2D, textIDs.at(i));
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textures.at(i).width, textures.at(i).height, 0, GL_RGB, GL_UNSIGNED_BYTE, textures.at(i).textureData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void GL_Context::loadVertsToGPU(std::vector<std::vector<float>> &verts, std::vector<std::vector<float>> &texels, std::vector<int> &vertIDs) {
    int numVerts = verts.at(0).size();
    numVBOs = verts.size() + texels.size();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, verts.at(0).size()*4, verts[0].data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, (texels.at(0)).size()*4, texels[0].data(), GL_STATIC_DRAW);
    vertIDs.push_back(0);
}

void GL_Context::init() {
    if (!glfwInit()) { Debug().reportError("Failed to init glfw"); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(800, 800, "SPHERE GAME", NULL, NULL); 
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { Debug().reportError("Failed to init glew"); }
    glfwSwapInterval(1);
    renderingProgram = createShaderProgram("vertShader.glsl", "fragShader.glsl");
    camera = Camera(Position(0.0f, 0.0f, 8.0f));
}

GLuint* GL_Context::getVAO() {
    return vao;
}

GLuint* GL_Context::getVBO() {
    return vbo;
}

void GL_Context::display(ObjectData &objData) {
    dt = glfwGetTime();
    Object* player = objData.getObject(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(renderingProgram);

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;

    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    vMat = glm::lookAt(camera.getPosition(), player->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    mMat = glm::translate(glm::mat4(1.0f), player->getPosition());

    mvMat = vMat * mMat;

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, objData.getTextID(0));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArrays(GL_TRIANGLES, 0, player->getNumVertices());
}

bool GL_Context::runSingleFrame(ObjectData &objData) {
    display(objData);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool GL_Context::windowShouldClose() {
    return glfwWindowShouldClose(window);
}

void GL_Context::updateTime() {
    dt = glfwGetTime();
}

float GL_Context::getTime() {
    return dt;
}