#pragma once
#include "../headers/Transform.h"

MatCore::Transform::Transform() {
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	modelMatrix = glm::mat4(1.f);
}

glm::mat4 MatCore::Transform::GetModelMatrix() {
	UpdateModelMatrix();
	return modelMatrix;
}

void MatCore::Transform::UpdateModelMatrix() {
	modelMatrix = glm::mat4(1.f);
	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	modelMatrix = glm::scale(modelMatrix, scale);
}