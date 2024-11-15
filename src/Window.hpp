#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow *window;
    int width, height;

    static void FramebufferSizeCallback(GLFWwindow *win, int width, int height);
    static void WindowSizeCallback(GLFWwindow *win, int width, int height);

public:
    Window(const std::string &title, int width, int height);
    ~Window();

    void Show();

    int GetWidth() const {
        return width;
    }

    int GetHeight() const {
        return height;
    }
};
