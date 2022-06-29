#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Material {
public:
	Material(const char* vertexShaderPath, const char* fragmentShaderPath);
	Material(const Material& materialCopy);
	~Material();

	unsigned int shaderID;

	/// Ustawia uniformy specyficzne dla entity (np. macierze)
	void SetSelfUniforms();
	/// Ustawia uniformy ogólne (np. œwiat³a)
	void SetUniforms();

	void SetMVPMatrix(glm::mat4 modelMatrix, glm::mat4 VPMatrix);
private:
	glm::mat4 mvpMatrix;
};