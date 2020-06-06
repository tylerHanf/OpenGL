#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

class Window {
    int screenWidth, screenHeight;
    float aspect;
    GLFWwindow* window;

    public:
        Window();
        ~Window();
        Window(int width, int height, std::string title);
        GLFWwindow* getWindow();
        int* getWidth();
        int* getHeight();
        float calcAspect();
};

#endif