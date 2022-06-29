#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Transform {
public:
	Transform();
	~Transform() = default;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 GetModelMatrix();

private:
	glm::mat4 modelMatrix;

	void UpdateModelMatrix();
};