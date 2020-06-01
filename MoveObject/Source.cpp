/**
 * First program where user input moves the object
 **/

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <string>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include "../Utils/Utils.h"
#include "../Utils/ImportedModel.h"

const int numVAOs = 1;
const int numVBOs = 2;

struct move_t {
	float speed;
	int right;
	int left;
} move;

float cameraX, cameraY, cameraZ;
float cameraMove, cameraSpeed;
float wheelLocX, wheelLocY, wheelLocZ;
float wheelMove, rotation;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint starTexture;
unsigned char* texture;

ImportedModel wheel("cube.obj");

GLuint mvLoc, projLoc;
int width, height, textureWidth, textureHeight;
float aspect;
glm::mat4 pMat, mMat, vMat, mvMat;


void setupVertices() {
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);
	
	//bind Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, wheel.vertices.size()*4, &wheel.vertices[0], GL_STATIC_DRAW);

	//bind texture verts
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, wheel.texels.size()*4, &wheel.texels[0], GL_STATIC_DRAW);
}

void setupTexture(const char* TfilePath) {
	texture = SOIL_load_image(TfilePath, &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &starTexture);
	glBindTexture(GL_TEXTURE_2D, starTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
		GLfloat anisoSetting = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
	}
}

void init(GLFWwindow* window) {
	move.speed = 0.2;

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	renderingProgram = createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = -20.0f; cameraY = 5.0f; cameraZ = 0.0f;
	wheelLocX = 1.0f; wheelLocY = 0.0f; wheelLocZ = 0.0f;
	wheelMove = 0.0f; rotation = 0.0f;
	textureWidth = 64; textureHeight = 64;
	setupVertices();
	setupTexture("Space_Stars1.png");
}

void setStates(GLFWwindow* window) {
	move.left = glfwGetKey(window, GLFW_KEY_LEFT);
	move.right = glfwGetKey(window, GLFW_KEY_RIGHT);
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;

	setStates(window);

	if (move.right == GLFW_PRESS) {
		wheelMove += move.speed;
		rotation += move.speed;
		std::cout << "Location: " << wheelMove << std::endl;
	}

	if (move.left == GLFW_PRESS) {
		wheelMove += -1*move.speed;
		rotation += -1*move.speed;

		std::cout << "Location: " << wheelMove << std::endl;
	}

	pMat = glm::perspective(1.0f, aspect, 0.1f, 1000.0f);

	vMat = glm::lookAt(glm::vec3(cameraX, cameraY, cameraZ), glm::vec3(wheelLocX, wheelLocY, wheelLocZ), 
			glm::vec3(0.0f, 1.0f, 0.0f));

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(wheelLocX, wheelLocY, wheelLocZ));
	mMat *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, wheelMove));
	mMat *= glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(1.0f, 0.0f, 0.0f));

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
	glBindTexture(GL_TEXTURE_2D, starTexture);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, wheel.numVertices);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		move.right = true;
	} 

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		move.left = true;
	}
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Imported Object", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	init(window);
	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
		glfwSetKeyCallback(window, key_callback);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}