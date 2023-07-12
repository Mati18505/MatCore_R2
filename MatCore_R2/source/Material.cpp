#include "pch.h"

#include "../headers/Material.h"
#include "Shader.h"
#include "Texture.h"

MatCore::Material::Material(const char* vertexShaderPath, const char* fragmentShaderPath){
	shaderID = Shader::Load(vertexShaderPath, fragmentShaderPath);
	mvpMatrix = glm::mat4(1.f);
	albedo = std::make_shared<Texture2D>("Resources/Textures/NoTexture.png");
}

MatCore::Material::Material(const Material& materialCopy) {
	LOG_CORE_WARN("Material copy constructor called!");
	this->mvpMatrix = materialCopy.mvpMatrix;
	this->shaderID = materialCopy.shaderID;
	albedo = std::make_shared<Texture2D>("Resources/Textures/NoTexture.png");
}

MatCore::Material::~Material()
{
	glDeleteProgram(shaderID); 
}

void MatCore::Material::SetSelfUniforms() {
	//Macierze
	glUseProgram(shaderID);
	auto mvpUniformPos = glGetUniformLocation(shaderID, "mvp");
	glUniformMatrix4fv(mvpUniformPos, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void MatCore::Material::SetUniforms() {
	if(albedo != nullptr) albedo->Bind(0);
}

void MatCore::Material::SetMVPMatrix(glm::mat4 modelMatrix, glm::mat4 VPMatrix)
{
	this->mvpMatrix = VPMatrix * modelMatrix;
}