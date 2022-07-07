#pragma once
#include <glm/glm.hpp>
#include "Application.h"
#include <crtdbg.h>


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
namespace MatCore {
    MatCore::Application* applicationP;
}
int main(void)
{
    using namespace MatCore;
    applicationP = new Application();
    applicationP->RunApp();
    delete applicationP;
    _CrtDumpMemoryLeaks();

    return 0;
}