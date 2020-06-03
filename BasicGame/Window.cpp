#include "Window.h"

#include <GLFW/glfw3.h>
#include "Error.h"
#include <string>

Window::Window() {
    screenWidth = 0;
    screenHeight = 0;
}

Window::~Window() {
    glfwDestroyWindow(window);
}

Window::Window(int width, int height, std::string title) {
    screenWidth = width;
    screenHeight = height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
}

GLFWwindow* Window::getWindow() {
    return window;
}