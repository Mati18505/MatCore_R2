#pragma once
#include <glm/glm.hpp>
#include "Application.h"


//Zmuszenie do odpalenia aplikacji na dedykowanym GPU
//NVIDIA
extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

//AMD
extern "C"
{
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main(void)
{
    Application application;
    application.RunApp();

    return 0;
}