#pragma once
#include "../headers/Application.h"
#include <glad/glad.h>
#include "GLFWWindow.h"
#include "../headers/Renderer.h"
#include <iostream>
#include <string>
#include <memory>
#include "Input.h"
#include "Scene.h"
#include "Log.h"
#include "Platform/Windows/WindowsInput.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#include "Events/ApplicationEvents.h"
#undef CreateWindow //windows

extern MatCore::Application* applicationP;
//TODO: przenieœæ t¹ inicjalizacjê do klasy okna GLFW
std::unique_ptr<MatCore::Input> MatCore::Input::instance = std::make_unique<WindowsInput>();

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", 
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

MatCore::Application::Application()
    :renderer(nullptr), scene(nullptr), window(nullptr)
{}
MatCore::Application::~Application() {
    delete this->renderer;
    delete this->scene;
}

void MatCore::Application::RunApp() {
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

void MatCore::Application::CreateWindow(){
    this->window = GLFWWindow::CreateWindow(windowWidth, windowHeight, false);
    GLFWWindow::SetWindowCallbacks(window, BIND_EVENT_FN(Application::OnEvent));
}

bool MatCore::Application::WindowShouldClose() {
    return GLFWWindow::ShouldClose(window);
}

void MatCore::Application::CloseWindow(){
    GLFWWindow::CloseWindow();
}

void MatCore::Application::InitGL() {
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);
    glViewport(0, 0, windowWidth, windowHeight);
}

void MatCore::Application::InitializeApp() {
    //Load and parse config
    LOG_CORE_INFO("Creating window...");
    CreateWindow();
    LOG_CORE_INFO("Initializing OpenGL...");
    InitGL();
    LOG_CORE_INFO("Creating scene...");
    assert(this->scene = ApplicationStart());
    LOG_CORE_INFO("Creating renderer...");
    this->renderer = new Renderer();
}

void MatCore::Application::MainLoop() {
    while (glGetError() != 0)
        continue;
    //TODO: przenieœæ delta time do fizyki? input?
    deltaTime = (glfwGetTime() - lastFrameAppTime) * 1000.;
    lastFrameAppTime = glfwGetTime();

    scene->Update();
    scene->BaseUpdate();
    renderer->RenderScene();
    scene->Render();
    //vsync ? glfwswapbuffers : glfinish
    glfwSwapBuffers(window);
    //input update
    glfwPollEvents();

    //Sprawdzanie error'ów OpenGL
    int error = glGetError();
    if (error != 0)
        LOG_CORE_ERROR("GLERROR: {0}", std::to_string(error));
}

bool MatCore::Application::WindowResizeCallback(WindowResizeEvent& e) {
    windowWidth = e.GetWidth();
    if (e.GetHeight() != 0)
    {
        windowHeight = e.GetHeight();
        scene->FrameBufferSizeCallback(e.GetWidth(), e.GetHeight());
    }
    return false;
}

void MatCore::Application::OnEvent(Event& e)
{
    scene->OnEvent(e);
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::WindowResizeCallback));
}