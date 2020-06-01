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

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint starTexture;
unsigned char* texture;

ImportedModel cube("GLBlender1-cube.obj");

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
	glBufferData(GL_ARRAY_BUFFER, cube.vertices.size()*4, &cube.vertices[0], GL_STATIC_DRAW);

	//bind texture verts
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, cube.texels.size()*4, &cube.texels[0], GL_STATIC_DRAW);

	/*bind normal verts
	glBindBuffer(GL_ARRAY_BUFFER, *norms);
	glBufferData(GL_ARRAY_BUFFER, (model->normals).size()*4, norms, GL_STATIC_DRAW);
	*/
}

void setupTexture(const char* TfilePath) {
	//glEnable(GL_TEXTURE_2D);
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

void init(GLFWwindow*window) {
	renderingProgram = createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 4.0f; cameraY = 0.0f; cameraZ = 2.0f;
	cubeLocX = 8.0f; cubeLocY = 0.0f; cubeLocZ = 0.0f;
	textureWidth = 64; textureHeight = 64;
	setupVertices();
	setupTexture("Space_Stars1.png");
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0f, aspect, 0.1f, 1000.0f);

	vMat = glm::lookAt(glm::vec3(cameraX, cameraY*2, cameraZ), glm::vec3(cubeLocX, cubeLocY, cubeLocZ), 
			glm::vec3(0.0f, 1.0f, 0.0f));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
	//mMat *= glm::rotate(glm::mat4(1.0f), 1.75f*(float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
	//mMat *= glm::rotate(glm::mat4(1.0f), 1.75f*(float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
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
	glBindTexture(GL_TEXTURE_2D, starTexture);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, cube.numVertices);
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(400, 400, "Imported Object", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	cube.printVertices();

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
