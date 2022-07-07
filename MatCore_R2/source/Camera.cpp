#pragma once
#include "../headers/Camera.h"
#include "Application.h"

MatCore::Camera::Camera(float fov, CameraType cameraType)
	:cameraType(cameraType), fov(fov), cameraPos({ 0.f, 0.f, 0.f }), cameraUp({ 0.f, 1.f, 0.f }),
	pitch(0.f), yaw(0.f), roll(0.f), size2D(1.f), nearClip(0.1f), farClip(1000.f)
{
	RecalculateViewMatrix();
	RecalculateProjectionMatrix();
	RecalculateVPMatrix();
}

void MatCore::Camera::FramebufferSizeCallback(int width, int height) {
	RecalculateProjectionMatrix();
	RecalculateVPMatrix();
}

void MatCore::Camera::RecalculateProjectionMatrix() {
	if (this->cameraType == CameraType::perspective)
		projectionMatrix = glm::perspective(glm::radians(fov), (float)(applicationP->windowWidth) / (applicationP->windowHeight), nearClip, farClip);
	else
		projectionMatrix = glm::ortho(-(applicationP->windowWidth / 2) * size2D, applicationP->windowWidth / 2 * size2D, -(applicationP->windowHeight / 2 * size2D), applicationP->windowHeight / 2 * size2D, nearClip, farClip);
}


void MatCore::Camera::RecalculateViewMatrix() {
	cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraFront.y = sin(glm::radians(pitch));
	cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(cameraFront);

	//Roll: obracamy wektor cameraUp w osi cameraFront o roll stopni
	glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(roll), cameraFront);
	glm::vec3 newCameraUp = glm::mat3(rollMatrix) * cameraUp;

	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, newCameraUp);
}

void MatCore::Camera::RecalculateVPMatrix() {
	vpMatrix = GetProjectionMatrix() * GetViewMatrix();
}