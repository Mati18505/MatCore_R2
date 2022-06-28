#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Application.h"
#include "Utils/Profiler.h"

class Shader
{
public:
    /// <summary>
    /// Reads and build the shader
    /// </summary>
    /// <param name="vertexPath">File path to vertex shader</param>
    /// <param name="fragmentPath">File path to fragment shader</param>
    static unsigned int Load(const char* vertexPath, const char* fragmentPath)
    {
        // 1. UZYSKANIE KODU èR”D£OWEGO SHADER”W Z PLIK”W
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            LogError("file_not_succesfully_read: "/* + e.what() + "\n"*/);
            return 0;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2.KOMPILACJA SHADER”W
        unsigned int vertex, fragment;


        // vertex shader

        //Tworzy pusty objekt shadera o podanym typie
        vertex = glCall(glCreateShader, GL_VERTEX_SHADER);

        //ZastÍpuje kod ürÛd≥owy podanego objektu shadera 
        //(parametry: 1.objekt shadera ktÛrego kod ma zostaÊ zastπpiony, 3.èrÛd≥o shadera jako tablica typu char)
        glCall(glShaderSource, vertex, 1, &vShaderCode, NULL);

        //Kompiluje shader (parametry:objekt shadera)
        glCall(glCompileShader, vertex);

        //Sprawdzanie powodzenia kompilacji shadera
        CheckCompileErrors(vertex, "VERTEX");


        // fragment Shader

        fragment = glCall(glCreateShader, GL_FRAGMENT_SHADER);
        glCall(glShaderSource, fragment, 1, &fShaderCode, NULL);
        glCall(glCompileShader, fragment);
        CheckCompileErrors(fragment, "FRAGMENT");


        // shader Program

        //Tworzenie programu shaderÛw
        unsigned int shaderID = glCall(glCreateProgram);

        //Do≥πczanie shaderÛw do programu
        glCall(glAttachShader, shaderID, vertex);
        glCall(glAttachShader, shaderID, fragment);

        //£πczenie shaderÛw w jednπ ca≥oúÊ
        glCall(glLinkProgram, shaderID);

        //Sprawdzanie powodzenia kompilacji shadera
        CheckCompileErrors(shaderID, "PROGRAM");

        //Po do≥πczeniu shaderÛw do programu usuwamy je poniewaø nie bÍdπ one juø potrzebne
        glCall(glDeleteShader, vertex);
        glCall(glDeleteShader, fragment);
        return shaderID;
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    static void CheckCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glCall(glGetShaderiv, shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glCall(glGetShaderInfoLog, shader, 1024, NULL, infoLog);
                Debug::Log("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- \n");
            }
        }
        else
        {
            glCall(glGetProgramiv, shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glCall(glGetProgramInfoLog, shader, 1024, NULL, infoLog);
                Debug::Log("ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- \n");
            }
        }
    }

};