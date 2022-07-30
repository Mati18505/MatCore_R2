#pragma once
#include "MatCore.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class EditorCamera : public MatCore::Camera {
public:
	EditorCamera() = default;
	~EditorCamera() = default;

	void OnEvent(MatCore::Event& e);
	void Update();

	glm::vec3 GetUpDirection() const;
	glm::vec3 GetRightDirection() const;
	glm::vec3 GetForwardDirection() const;
	glm::quat GetOrientation() const;

	float FOV = 90;
	glm::vec3 center{ 0, 0, 0 };
	float distance = 10;
	static double mouseSensitivity;
	float aspectRatio = 16.f / 9;

private:
	void UpdateView();
	void UpdateProjection();
	void PanView(glm::vec2 offset);
	void RotateView(glm::vec2 offset);

	float pitch = 0;
	float yaw = 0;
	glm::vec3 position{ 0, 0, 0 };

	glm::vec2 lastMousePos{ 0, 0 };
	glm::vec3 offsetDir{ 0, 0, 1 };

	float lastDistance = 10;
};