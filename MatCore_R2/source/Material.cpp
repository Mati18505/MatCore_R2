#pragma once
#include "../headers/Material.h"
#include "OpenGL/Shader.h"
#include <glad/glad.h>

MatCore::Material::Material(Resource<Shader>& vs, Resource<Shader>& ps)
	: shader(Factory::Get().CreateShaderProgramAssetFromShaders(vs, ps))
{}

void MatCore::Material::SetSelfUniforms() {
	//Macierze
	auto& s = shader.GetBuffer();
	s->Bind();
	auto mvpUniformPos = glGetUniformLocation(s->GetHandle(), "mvp");
	glUniformMatrix4fv(mvpUniformPos, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void MatCore::Material::SetUniforms() {
	albedo.GetBuffer()->Bind(0);
}

void MatCore::Material::SetMVPMatrix(glm::mat4 modelMatrix, glm::mat4 VPMatrix)
{
	this->mvpMatrix = VPMatrix * modelMatrix;
}