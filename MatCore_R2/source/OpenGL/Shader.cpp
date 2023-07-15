#include "pch.h"

#include "OpenGL/Shader.h"
#include <glad/glad.h>

MatCore::Shader::~Shader() {
	glDeleteShader(shader);
}
