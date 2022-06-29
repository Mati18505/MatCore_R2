#pragma once
#include "../headers/Application.h"
#include <glad.h>
#include "GLFWWindow.h"
#include "../headers/Renderer.h"
#include <iostream>
#include <string>
#include <crtdbg.h>
#include "Scene.h"

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
    //Load and parse config
    CreateWindow();
    InitGL();
    this->scene = new Scene();
    scene->Start();
    this->renderer = new Renderer();

    while (!WindowShouldClose())
        MainLoop();

    CloseWindow();
    _CrtDumpMemoryLeaks();
}

void Application::CreateWindow(){
    this->window = GLFWWindow::CreateWindow(800, 600, false);
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

void Application::MainLoop() {
    //delta time
    scene->Update();
    //camera update
    renderer->RenderScene();
    //vsync ? glfwswapbuffers : glfinish
    glfwSwapBuffers(window);
    //input update
    glfwPollEvents();

    //Sprawdzanie error'ów OpenGL
    int error = glGetError();
    if (error != 0)
        std::cout<<"GLERROR: " << std::to_string(error) << std::endl;
    glDebugMessageCallback(MessageCallback, 0);
}