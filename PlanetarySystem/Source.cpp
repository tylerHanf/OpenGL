#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <cmath>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utils/Utils.h"
#include <stdio.h>

#define numVAOs 1
#define numVBOs 3

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
float pyrLocX, pyrLocY, pyrLocZ;
float tetraLocX, tetraLocY, tetraLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, mMat, vMat, mvMat;

std::stack<glm::mat4> mvStack;

void setupVertices(void) {
        float cubePositions[108] = {
              -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
              1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
              1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
              1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
              1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
              -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
              -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
              -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
              -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
              1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
              -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
              1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
        };

        float pyramidPositions[54] = {
                -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f
        };

	float tetraPositions[36] = {
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f
	};

        glGenVertexArrays(numVAOs, vao);
        glBindVertexArray(vao[0]);
        glGenBuffers(numVBOs, vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tetraPositions), tetraPositions, GL_STATIC_DRAW);
}

void init(GLFWwindow* window) {
        renderingProgram = createShaderProgram("vertShader.glsl", "fragShader.glsl");
        cameraX = 0.0f; cameraY = 0.0f; cameraZ = 20.0f;
        cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
        pyrLocX = 3.0f; pyrLocY = 2.0f; pyrLocZ = -8.0f;
	tetraLocX = -1.0f; tetraLocY = 4.0f; tetraLocZ = 2.0f;
        setupVertices();
}

void display(GLFWwindow* window, double currentTime) {
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(renderingProgram);

        mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
        projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

        glfwGetFramebufferSize(window, &width, &height);
        aspect = (float)width / (float)height;
        pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

        vMat = glm::lookAt(glm::vec3(cameraX, cameraY*5.0, cameraZ), glm::vec3(pyrLocX, pyrLocY, pyrLocZ), glm::vec3(0.0f, 1.0f, 0.0f));

	mvStack.push(vMat);

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//Pyramid->Sun
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 18);
	mvStack.pop();

	//Tetra->Planet
	mvStack.push(mvStack.top());

	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)currentTime)*4.0, 
				cos((float)currentTime)*8.0));

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 12);
	mvStack.pop();

	//Cube->Planet
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime)*4.0, 0.0f, 
				cos((float)currentTime)*4.0));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0, 1.0, 0.0));

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);
	mvStack.pop();

	//Small Cube->Moon
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime)*4.0, 0.0,
				cos((float)currentTime*2.0)));
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime, glm::vec3(1.0, 0.0, 0.0));
	mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f)); 
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
 	mvStack.pop(); mvStack.pop(); mvStack.pop(); mvStack.pop();
}

int main(void) {
        if (!glfwInit()) { exit(EXIT_FAILURE); }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        GLFWwindow* window = glfwCreateWindow(800, 800, "MultiObjects", NULL, NULL);
        glfwMakeContextCurrent(window);
        if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
        glfwSwapInterval(1);

        init(window);
        while (!glfwWindowShouldClose(window)) {
                display(window, glfwGetTime());
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
}
