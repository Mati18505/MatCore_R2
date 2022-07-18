#pragma once
#include "../headers/Transform.h"

glm::mat4 MatCore::Transform::GetModelMatrix() {
	UpdateModelMatrix();
	return modelMatrix;
}

void MatCore::Transform::UpdateModelMatrix() {
	modelMatrix = glm::mat4(1.f);
	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), { 1, 0, 0 });
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), { 0, 1, 0 });
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), { 0, 0, 1 });

	modelMatrix = glm::scale(modelMatrix, scale);
}