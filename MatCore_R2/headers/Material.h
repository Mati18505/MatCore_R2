#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
typedef unsigned int ShaderID;

struct Material {
public:
	Material(const char* vertexShaderPath, const char* fragmentShaderPath);
	Material(const Material& materialCopy) = default;
	~Material();

	ShaderID shaderID;
	glm::mat4 mvpMatrix;

	/// <summary>
	/// Ustawia uniformy specyficzne dla Renderer (np. macierze)
	/// </summary>
	void SetSelfUniforms();
	/// <summary>
	/// Ustawia uniformy ogólne (np. œwiat³a)
	/// </summary>
	void SetUniforms();

	virtual void SetMVPMatrix(glm::mat4 modelMatrix, glm::mat4 VPMatrix) {
		this->mvpMatrix = VPMatrix * modelMatrix;
	}
};