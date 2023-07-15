#include "pch.h"

#include "OpenGL/ShaderProgram.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

MatCore::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(handle);
}

void MatCore::ShaderProgram::Bind() const {
	glUseProgram(handle);
}

void MatCore::ShaderProgram::SetUniform(const std::string& name, int value)
{
	int pos = GetUniformLocation(name);
	glUniform1i(pos, value);
}

void MatCore::ShaderProgram::SetUniform(const std::string& name, float value)
{
	int pos = GetUniformLocation(name);
	glUniform1f(pos, value);
}

void MatCore::ShaderProgram::SetUniform(const std::string& name, const glm::vec2& value)
{
	int pos = GetUniformLocation(name);
	glUniform2f(pos, value.x, value.y);
}

void MatCore::ShaderProgram::SetUniform(const std::string& name, const glm::vec3& value)
{
	int pos = GetUniformLocation(name);
	glUniform3f(pos, value.x, value.y, value.z);
}

void MatCore::ShaderProgram::SetUniform(const std::string& name, const glm::vec4& value)
{
	int pos = GetUniformLocation(name);
	glUniform4f(pos, value.x, value.y, value.z, value.w);
}

void MatCore::ShaderProgram::SetUniform(const std::string& name, const glm::mat3& value)
{
	int pos = GetUniformLocation(name);
	glUniformMatrix3fv(pos, 1, GL_FALSE, glm::value_ptr(value));
}

void MatCore::ShaderProgram::SetUniform(const std::string& name, const glm::mat4& value)
{
	int pos = GetUniformLocation(name);
	glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(value));
}

int MatCore::ShaderProgram::GetUniformLocation(const std::string& name)
{
	return glGetUniformLocation(handle, name.c_str());
}
