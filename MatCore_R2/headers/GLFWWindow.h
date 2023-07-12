#pragma once
#include <GLFW/glfw3.h>
#include "Log.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#undef CreateWindow
namespace MatCore {
    namespace GLFWWindow {
        using EventCallbackFn = std::function<void(Event&)>;
        struct WindowData {
            EventCallbackFn callbackFn;
        };
        WindowData data;
        GLFWwindow* CreateWindow(int windowWidth, int windowHeight, bool fullscreen) {

            using namespace std;

            if (!glfwInit()) {
                LOG_CORE_CRITICAL("GLFW init failed!");
                return nullptr;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            /*glfwWindowHint(GLFW_DOUBLEBUFFER, windowProperties.VSync);
            glfwWindowHint(GLFW_DECORATED, !(windowProperties.borderlessWindow));
            glfwWindowHint(GLFW_MAXIMIZED, windowProperties.borderlessWindow);
            glfwWindowHint(GLFW_FOCUSED, windowProperties.focusOnStart);*/
            glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

            GLFWmonitor* windowMonitor;
            windowMonitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;

            GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "MatCore", windowMonitor, nullptr);
            if (window == nullptr) {
                LOG_CORE_CRITICAL("GLFW window creation failed!");
                return nullptr;
            }

            glfwMakeContextCurrent(window);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSwapInterval(1);
            return window;
        }

        void SetWindowCallbacks(GLFWwindow* window, const EventCallbackFn& eventCallback)
        {
            data.callbackFn = eventCallback;
            glfwSetWindowUserPointer(window, &data.callbackFn);
            glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
                EventCallbackFn& callbackFn = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
                WindowCloseEvent e;
                callbackFn(e);
            });
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
                EventCallbackFn& callbackFn = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
                WindowResizeEvent e(width, height);
                callbackFn(e);
            });
            
            glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                EventCallbackFn& callbackFn = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent e(key, false);
                    callbackFn(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent e(key);
                    callbackFn(e);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent e(key, true);
                    callbackFn(e);
                    break;
                }
                }
            });

            glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
                EventCallbackFn& callbackFn = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent e(button);
                    callbackFn(e);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent e(button);
                    callbackFn(e);
                    break;
                }
                }
            });

            glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
                EventCallbackFn& callbackFn = *(EventCallbackFn*)glfwGetWindowUserPointer(window);

                MouseMovedEvent e((float)xpos, (float)ypos);
                callbackFn(e);
            });
            glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
                EventCallbackFn& callbackFn = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
                MouseScrolledEvent e(xoffset, yoffset);
                callbackFn(e);
            });
        }

        void CloseWindow() {
            glfwTerminate();
        }

        bool ShouldClose(GLFWwindow* window) {
            return glfwWindowShouldClose(window);
        }
    }
}