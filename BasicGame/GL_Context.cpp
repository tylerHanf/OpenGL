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

GL_Context::GL_Context(LoadData *ld) { 
    init();
    testSetup();
    testTextLoad();
    //loadVertsToGPU(ld->getVertices(), ld->getTexels(), ld->getVertIDs());
    //loadTexToGPU(ld->getTextures(), ld->getTextIDs());
}

GL_Context::~GL_Context() {
    glfwTerminate();
}

GLFWwindow* GL_Context::getWindow() {
    return window;
}

void GL_Context::loadTexToGPU(std::vector<Texture*> *textures, std::vector<GLuint> *textIDs) {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(textures->size(), &(*textIDs)[0]);
    for (int i=0; i<textures->size(); i++) {
        textIDs->push_back(i);
        glBindTexture(GL_TEXTURE_2D, (*textIDs)[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*textures)[i]->width, (*textures)[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, (*textures)[i]->textureData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void GL_Context::loadVertsToGPU(std::vector<std::vector<float>> *verts, std::vector<std::vector<float>> *texels, std::vector<int> *vertIDs) {
    numVBOs = verts->size() + texels->size();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, verts->size()*4, &(*verts)[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, texels->size()*4, &(*texels)[0], GL_STATIC_DRAW);
    vertIDs->push_back(0);
    //Need to store vert buffer then texture buffer sequentually
    //in VBO, but must not duplicate vbo indices
    /*for (int i=0, j=0; i<verts->size(); i++, j+=2) {
        //Load Verts
        glBindBuffer(GL_ARRAY_BUFFER, vbo[j]);
        glBufferData(GL_ARRAY_BUFFER, (*verts)[i].size()*4, &(*verts)[i], GL_STATIC_DRAW);

        //Load Texels
        glBindBuffer(GL_ARRAY_BUFFER, vbo[j+1]);
        glBufferData(GL_ARRAY_BUFFER, (*texels)[i].size()*4, &(*texels)[i], GL_STATIC_DRAW);
        vertIDs->push_back(j);
    }
    */
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
    camera = new Camera(Position(0.0f, 0.0f, 8.0f));
}

GLuint* GL_Context::getVAO() {
    return vao;
}

GLuint* GL_Context::getVBO() {
    return vbo;
}

void GL_Context::display(ObjectData objData) {
    double currenTime = glfwGetTime();
    //Object* player = objData.getObject(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(renderingProgram);

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;

    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
    vMat = glm::lookAt(camera->getPosition(), glm::vec3(8.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, 0.0f));
    /*vMat = glm::lookAt(camera->getPosition(), player->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    mMat = glm::translate(glm::mat4(1.0f), player->getPosition());
    */

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
    //glBindTexture(GL_TEXTURE_2D, objData.getTextID(0));
    glBindTexture(GL_TEXTURE_2D, rockTex);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //glDrawArrays(GL_TRIANGLES, 0, player->getNumVertices());
    glDrawArrays(GL_TRIANGLES, 0, 12);
}

bool GL_Context::renderLoop(ObjectData objData) {
    while (!glfwWindowShouldClose(window)) {
        display(objData);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GL_Context::testSetup() {
	float tetraPositions[36] = {
                -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f
        };

	float tetraTexCoords[24] = {
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f
	};

	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tetraPositions), tetraPositions, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tetraTexCoords), tetraTexCoords, GL_STATIC_DRAW);
}

void GL_Context::testTextLoad() {
    glEnable(GL_TEXTURE_2D);
    img = SOIL_load_image("Assets/Textures/Space_Stars1.png", &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
    glGenTextures(1, &rockTex);
    glBindTexture(GL_TEXTURE_2D, rockTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
        GLfloat anisoSetting = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
    }
}