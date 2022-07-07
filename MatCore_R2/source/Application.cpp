#pragma once
#include "../headers/Application.h"
#include <glad.h>
#include "GLFWWindow.h"
#include "../headers/Renderer.h"
#include <iostream>
#include <string>
#include "Scene.h"
#include "Camera.h"
#include "Log.h"
#undef CreateWindow //windows

extern Application* applicationP;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", 
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

Application::Application(){
    renderer = nullptr;
    scene = nullptr;
}
Application::~Application() {
    delete this->renderer;
    delete this->scene;
}

void Application::RunApp() {
    Log::Init();
    LOG_CORE_INFO("Initializing app...");
    InitializeApp();
    LOG_CORE_INFO("App initialized!");
    LOG_CORE_INFO("Starting...");
    scene->Start();

    while (!WindowShouldClose())
        MainLoop();

    LOG_CORE_INFO("Closing...");
    CloseWindow();
}

void Application::CreateWindow(){
    this->window = GLFWWindow::CreateWindow(800, 600, false);
    GLFWWindow::SetWindowCallbacks(window, WindowFramebufferSizeCallback, WindowCursorPosCallback, WindowKeyCallback, WindowMouseButtonCallback);
}

bool Application::WindowShouldClose() {
    return GLFWWindow::ShouldClose(window);
}

void Application::CloseWindow(){
    GLFWWindow::CloseWindow();
}

void Application::InitGL() {
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEBUG_OUTPUT);
    glViewport(0, 0, windowWidth, windowHeight);
}

void Application::InitializeApp() {
    //Load and parse config
    LOG_CORE_INFO("Creating window...");
    CreateWindow();
    LOG_CORE_INFO("Initializing OpenGL...");
    InitGL();
    LOG_CORE_INFO("Creating scene...");
    this->scene = new Scene();
    LOG_CORE_INFO("Creating renderer...");
    this->renderer = new Renderer();
}

void Application::MainLoop() {
    //delta time
    scene->Update();
    renderer->RenderScene();
    //vsync ? glfwswapbuffers : glfinish
    glfwSwapBuffers(window);
    //input update
    glfwPollEvents();

    //Sprawdzanie error'ów OpenGL
    int error = glGetError();
    if (error != 0)
        LOG_CORE_ERROR("GLERROR: {0}", std::to_string(error));
    glDebugMessageCallback(MessageCallback, 0);
}

void Application::WindowFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    applicationP->windowWidth = width;
    applicationP->windowHeight = height;
    applicationP->scene->camera->FramebufferSizeCallback(width, height);
}

void Application::WindowCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {

}

void Application::WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){

}

void Application::WindowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods){

}