#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Log.h"

namespace MatCore {
    class ShaderLoader
    {
    public:
        static std::string LoadFileToShaderCode(const std::string& filePath);

        enum class ShaderType {
            vertex,
            fragment
        };

        static uint32_t CompileShader(const std::string& shaderCode, ShaderType shaderType);

        static unsigned int CreateShaderProgram(unsigned int vs, unsigned int fs);

    private:
        static void CheckCompileErrorsForShader(unsigned int shader, ShaderType shaderType);

        static void CheckCompileErrorsForShaderProgram(unsigned int shader);

        static unsigned int GetGLShaderType(ShaderType shaderType);
        static std::string ToString(ShaderType shaderType);

    };
}