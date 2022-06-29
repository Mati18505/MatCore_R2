#pragma once
#include "../headers/Application.h"
#include <glad.h>
#include "GLFWWindow.h"
#include "../headers/Renderer.h"
#include <iostream>
#include <string>
#include <crtdbg.h>
#include "Scene.h"

Application::Application(){
    renderer = nullptr;
    scene = nullptr;
    window = nullptr;
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
}