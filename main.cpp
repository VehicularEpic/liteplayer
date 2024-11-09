#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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

static int Run() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return EXIT_FAILURE;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Lite Music Player", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

#ifdef WIN32
    HWND hwnd = glfwGetWin32Window(window);
    _WndProc = (WNDPROC) GetWindowLongPtr(hwnd, GWLP_WNDPROC);
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR) WndProc);
#endif

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

#ifdef WIN32
int APIENTRY
WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    return Run();
}
#else
int main(int argc, char const *argv[]) {
    return Run();
}
#endif
