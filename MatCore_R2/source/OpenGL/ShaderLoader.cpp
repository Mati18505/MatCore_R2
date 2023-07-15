#include "pch.h"

#include "OpenGL/ShaderLoader.h"
#include <glad/glad.h>

std::string MatCore::ShaderLoader::LoadFileToShaderCode(const std::string& filePath)
{
    // 1. UZYSKANIE KODU èR”D£OWEGO SHADER”W Z PLIK”W
    std::string vertexCode;
    std::ifstream vShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(filePath.c_str());
        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        LOG_CORE_ERROR("file_not_succesfully_read: {0}", e.what());
        assert(false);
    }
    return vertexCode;
}

uint32_t MatCore::ShaderLoader::CompileShader(const std::string& shaderCode, ShaderType shaderType)
{
    const char* shaderCodePtr = shaderCode.c_str();
    uint32_t shader;
    shader = glCreateShader(GetGLShaderType(shaderType));
    glShaderSource(shader, 1, &shaderCodePtr, NULL);
    glCompileShader(shader);
    CheckCompileErrorsForShader(shader, shaderType);
    return shader;
}

unsigned int MatCore::ShaderLoader::CreateShaderProgram(unsigned int vs, unsigned int fs)
{
    unsigned int shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vs);
    glAttachShader(shaderProgramID, fs);
    glLinkProgram(shaderProgramID);
    CheckCompileErrorsForShaderProgram(shaderProgramID);
    return shaderProgramID;
}

void MatCore::ShaderLoader::CheckCompileErrorsForShader(unsigned int shader, ShaderType shaderType)
{
    int success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        LOG_CORE_ERROR("Shader compilation error of type: {0}\n{1}", ToString(shaderType), infoLog);
    }
}

void MatCore::ShaderLoader::CheckCompileErrorsForShaderProgram(unsigned int shader)
{
    int success;
    char infoLog[1024];

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        LOG_CORE_ERROR("PROGRAM_LINKING_ERROR of type : {0}\n{1}", "PROGRAM", infoLog);
    }
}

GLuint MatCore::ShaderLoader::GetGLShaderType(ShaderType shaderType)
{
    GLuint glShaderType;

    switch (shaderType)
    {
    case ShaderType::vertex:
        glShaderType = GL_VERTEX_SHADER;
        break;
    case ShaderType::fragment:
        glShaderType = GL_FRAGMENT_SHADER;
        break;
    }
    return glShaderType;
}

std::string MatCore::ShaderLoader::ToString(ShaderType shaderType)
{
    std::string string;

    switch (shaderType)
    {
    case ShaderType::vertex:
        string = "VERTEX";
        break;
    case ShaderType::fragment:
        string = "FRAGMENT";
        break;
    }
    return string;
}