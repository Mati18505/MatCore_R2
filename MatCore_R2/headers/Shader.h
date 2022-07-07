#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad.h>
#include "Log.h"
namespace MatCore {
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
                LOG_CORE_ERROR("file_not_succesfully_read: {0}", e.what());
                return 0;
            }
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            // 2.KOMPILACJA SHADER”W
            unsigned int vertex, fragment;


            // vertex shader

            //Tworzy pusty objekt shadera o podanym typie
            vertex = glCreateShader(GL_VERTEX_SHADER);

            //ZastÍpuje kod ürÛd≥owy podanego objektu shadera 
            //(parametry: 1.objekt shadera ktÛrego kod ma zostaÊ zastπpiony, 3.èrÛd≥o shadera jako tablica typu char)
            glShaderSource(vertex, 1, &vShaderCode, NULL);

            //Kompiluje shader (parametry:objekt shadera)
            glCompileShader(vertex);

            //Sprawdzanie powodzenia kompilacji shadera
            CheckCompileErrors(vertex, "VERTEX");


            // fragment Shader

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            CheckCompileErrors(fragment, "FRAGMENT");


            // shader Program

            //Tworzenie programu shaderÛw
            unsigned int shaderID = glCreateProgram();

            //Do≥πczanie shaderÛw do programu
            glAttachShader(shaderID, vertex);
            glAttachShader(shaderID, fragment);

            //£πczenie shaderÛw w jednπ ca≥oúÊ
            glLinkProgram(shaderID);

            //Sprawdzanie powodzenia kompilacji shadera
            CheckCompileErrors(shaderID, "PROGRAM");

            //Po do≥πczeniu shaderÛw do programu usuwamy je poniewaø nie bÍdπ one juø potrzebne
            glDeleteShader(vertex);
            glDeleteShader(fragment);
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
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    LOG_CORE_ERROR("Shader compilation error of type: {0}\n{1}", type, infoLog);
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    LOG_CORE_ERROR("PROGRAM_LINKING_ERROR of type : {0}\n{1}", type, infoLog);
                }
            }
        }

    };
}