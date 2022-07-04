#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include "Log.h"
#undef CreateWindow

namespace GLFWWindow {
    GLFWwindow* CreateWindow(int windowWidth, int windowHeight, bool fullscreen) {

        using namespace std;

        if (!glfwInit()) {
            LOG_CORE_CRITICAL("GLFW init failed!");
            return nullptr;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /*glfwWindowHint(GLFW_DOUBLEBUFFER, windowProperties.VSync);
        glfwWindowHint(GLFW_DECORATED, !(windowProperties.borderlessWindow));
        glfwWindowHint(GLFW_MAXIMIZED, windowProperties.borderlessWindow);
        glfwWindowHint(GLFW_FOCUSED, windowProperties.focusOnStart);*/
        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

        GLFWmonitor* windowMonitor;
        windowMonitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;

        GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "MatCore", windowMonitor, nullptr);
        if (window == nullptr) {
            LOG_CORE_CRITICAL("GLFW window creation failed!");
            return nullptr;
        }

        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSwapInterval(1);
        return window;
    }

    void SetWindowCallbacks(GLFWwindow* window, void(*FramebufferSizeCallback)(GLFWwindow*, int, int), void(*CursorPosCallback)(GLFWwindow*, double, double),
        void(*KeyCallback)(GLFWwindow*, int, int, int, int), void(*MouseButtonCallback)(GLFWwindow*, int, int, int)) 
    {
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
    }

    void CloseWindow() {
        glfwTerminate();
    }

    bool ShouldClose(GLFWwindow* window) {
        return glfwWindowShouldClose(window);
    }
}