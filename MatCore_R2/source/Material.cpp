#pragma once
#include "../headers/Material.h"
#include "Shader.h"

Material::Material(const char* vertexShaderPath, const char* fragmentShaderPath){
	shaderID = Shader::Load(vertexShaderPath, fragmentShaderPath);
	mvpMatrix = glm::mat4(1.f);
}

Material::Material(const Material& materialCopy) {
	LOG_CORE_WARN("Material copy constructor called!");
	this->mvpMatrix = materialCopy.mvpMatrix;
	this->shaderID = materialCopy.shaderID;
}

Material::~Material()
{
	glDeleteProgram(shaderID); 
}

void Material::SetSelfUniforms() {
	//Macierze
	glUseProgram(shaderID);
	auto mvpUniformPos = glGetUniformLocation(shaderID, "mvp");
	glUniformMatrix4fv(mvpUniformPos, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void Material::SetMVPMatrix(glm::mat4 modelMatrix, glm::mat4 VPMatrix)
{
	this->mvpMatrix = VPMatrix * modelMatrix;
}