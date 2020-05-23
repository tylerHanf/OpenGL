#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include "../Utils/Utils.h"
#include "../Utils/ImportedModel.h"

int main(void) {
	ImportedModel model("cube.obj");
	model.printVertices();
	return EXIT_SUCCESS;
}
