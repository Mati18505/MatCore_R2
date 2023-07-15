#include "pch.h"

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

MatCore::Application* applicationP;

int main(void)
{
    //sprawdzanie przecieków pamięci po zamknięciu programu
    int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpFlag);

    using namespace MatCore;
    applicationP = new Application();
    applicationP->RunApp();
    delete applicationP;

    return 0;
}