#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Debug.h"
#include <string>
#include "Window.h"

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

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
}

GLFWwindow* Window::getWindow() {
    return window;
}

int* Window::getWidth() {
    return &screenWidth;
}

int* Window::getHeight() {
    return &screenHeight;
}

float Window::calcAspect() {
    return (float) screenWidth / (float) screenHeight;
}