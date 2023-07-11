#include "OpenGL/Shader.h"
#include <glad/glad.h>

MatCore::Shader::Shader(Shader&& other) noexcept
	: shader(other.shader)
{
	other.shader = 0;
}

MatCore::Shader::~Shader() {
	glDeleteShader(shader);
}
