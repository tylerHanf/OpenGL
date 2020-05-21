#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <string>
#include <cmath>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utils/Utils.h"
#include <stdio.h>

#define numVAOs 1
#define numVBOs 2

float cameraX, cameraY, cameraZ;
float tetraLocX, tetraLocY, tetraLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint rockTex; 
unsigned char* img;

GLuint mvLoc, projLoc;
int width, height, imgWidth, imgHeight;
float aspect;
glm::mat4 pMat, mMat, vMat, mvMat;

void setupVertices(void) {
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

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 4.0f; cameraY = 0.0f; cameraZ = 10.0f;
	tetraLocX = 8.0f; tetraLocY = 0.0f; tetraLocZ = 0.0f;
	imgWidth = 64; imgHeight = 64;
	setupVertices();
	glEnable(GL_TEXTURE_2D);
	img = SOIL_load_image("Space_Stars1.png", &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &rockTex);
	glBindTexture(GL_TEXTURE_2D, rockTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
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

	vMat = glm::lookAt(glm::vec3(cameraX, cameraY*2, cameraZ), glm::vec3(tetraLocX, tetraLocY, tetraLocZ), 
			glm::vec3(0.0f, 1.0f, 0.0f));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(tetraLocX, tetraLocY, tetraLocZ));
	mMat *= glm::rotate(glm::mat4(1.0f), 1.75f*(float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
	mMat *= glm::rotate(glm::mat4(1.0f), 1.75f*(float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	mMat *= glm::rotate(glm::mat4(1.0f), 1.75f*(float)currentTime, glm::vec3(0.0f, 0.0f, 0.5f));
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
	glBindTexture(GL_TEXTURE_2D, rockTex);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, 12);
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(800, 800, "FirstTexture", NULL, NULL);
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
