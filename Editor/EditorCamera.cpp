#include "EditorCamera.h"
#include <glm/gtx/quaternion.hpp>

using namespace MatCore;
double EditorCamera::mouseSensitivity = 0.001f;

glm::quat EditorCamera::GetOrientation() const {
	return glm::quat(glm::vec3(-pitch, -yaw, 0));
}

void EditorCamera::UpdateView() {
	viewMatrix = glm::translate(glm::mat4(1.f), position) * glm::toMat4(GetOrientation());
	viewMatrix = glm::inverse(viewMatrix);
}

void EditorCamera::UpdateProjection(){
	projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 2000.f);
}

void EditorCamera::PanView(glm::vec2 offset)
{
	glm::normalize(offset);
	double sensitivity = mouseSensitivity * 0.142857 * distance;
		
	center -= GetRightDirection() * offset.x * float(applicationP->deltaTime * sensitivity);
	center -= GetUpDirection() * -offset.y * float(applicationP->deltaTime * sensitivity);
}

void EditorCamera::RotateView(glm::vec2 offset)
{
	glm::normalize(offset);
	pitch += offset.y * applicationP->deltaTime * mouseSensitivity;
	yaw += offset.x * applicationP->deltaTime * mouseSensitivity;
	offsetDir = -GetForwardDirection();
}

static float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

void EditorCamera::Update() {
	float newDistance = lerp(lastDistance, distance, 0.5f);
	position = center + offsetDir * newDistance;
	lastDistance = newDistance;

	UpdateView();
	UpdateProjection();
}

void EditorCamera::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseMovedEvent>([&](MouseMovedEvent& e) 
	{
		auto [x, y] = std::pair(e.GetX(), e.GetY());
		glm::vec2 offset{ x - lastMousePos.x, y - lastMousePos.y };

		if (Input::IsMouseButtonPressed(MC_MOUSE_BUTTON_3)) {
			if (Input::IsKeyPressed(MC_KEY_LEFT_SHIFT))
				PanView(offset);
			else
				RotateView(offset);
		}
		
		lastMousePos = { x, y };
		return true;
	});
	dispatcher.Dispatch<MouseScrolledEvent>([&](MouseScrolledEvent& e) 
	{
		distance += glm::pow(distance, 1.2)/20 * -e.GetYOffset() * applicationP->deltaTime/10;
		distance = glm::max(distance, 1.5f);
		return true;
	});
}

glm::vec3 EditorCamera::GetUpDirection() const
{
	return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 EditorCamera::GetRightDirection() const
{
	return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 EditorCamera::GetForwardDirection() const
{
	return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}