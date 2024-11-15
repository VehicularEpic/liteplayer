#include "Window.hpp"

#include <exception>
#include <iostream>

#ifdef WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

static WNDPROC _WndProc;

static LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_APPCOMMAND) {
        return 1;
    }

    return CallWindowProc(_WndProc, hwnd, message, wParam, lParam);
}
#endif

#include <glad/gl.h>

static void error_callback(int error, const char *description) {
    std::cerr << "Error: " << description << std::endl;
}

void Window::FramebufferSizeCallback(GLFWwindow *win, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::WindowSizeCallback(GLFWwindow *win, int width, int height) {
    Window *window = (Window *) glfwGetWindowUserPointer(win);

    window->width = width;
    window->height = height;
}

Window::Window(const std::string &title, int width, int height)
    : width(width), height(height) {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(window, this); // this Window instance

#ifdef WIN32
    HWND hwnd = glfwGetWin32Window(window);
    _WndProc = (WNDPROC) GetWindowLongPtr(hwnd, GWLP_WNDPROC);
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR) WndProc);
#endif

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, Window::FramebufferSizeCallback);
    glfwSetWindowSizeCallback(window, Window::WindowSizeCallback);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::Show() {
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
