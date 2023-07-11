#include "OpenGL/ShaderProgram.h"
#include <glad/glad.h>

MatCore::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(handle);
}

void MatCore::ShaderProgram::Bind() const {
	glUseProgram(handle);
}
