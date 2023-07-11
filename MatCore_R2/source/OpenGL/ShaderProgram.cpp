#include "OpenGL/ShaderProgram.h"
#include <glad/glad.h>

inline MatCore::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(handle);
}

inline void MatCore::ShaderProgram::Bind() const {
	glUseProgram(handle);
}
