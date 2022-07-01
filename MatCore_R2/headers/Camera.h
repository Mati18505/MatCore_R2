#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Application;
extern Application* applicationP;//= applicationP z pliku MatCore_R2.cpp

class Camera {
public:
	enum class CameraType {
		orthographic,
		perspective
	};
	

	Camera(float fov, CameraType cameraType);

	void SetCameraType(CameraType cameraType) {
		this->cameraType = cameraType;
		RecalculateProjectionMatrix();
		RecalculateVPMatrix();
	}
	void SetYaw(float yaw) {
		this->yaw = yaw;
		RecalculateViewMatrix();
		RecalculateVPMatrix();
	}
	void SetPitch(float pitch) {
		this->pitch = pitch;
		RecalculateViewMatrix();
		RecalculateVPMatrix();
	}
	void SetRoll(float roll) {
		this->roll = roll;
		RecalculateViewMatrix();
		RecalculateVPMatrix();
	}
	void SetFov(float fov) {
		this->fov = fov;
		RecalculateProjectionMatrix();
		RecalculateVPMatrix();
	}
	void SetSize2D(float size) {
		this->size2D = size;
		RecalculateProjectionMatrix();
		RecalculateVPMatrix();
	}
	void SetCameraClip(float near, float far) {
		this->nearClip = near;
		this->farClip = far;
		RecalculateProjectionMatrix();
		RecalculateVPMatrix();
	}
	void SetCameraPos(glm::vec3 position) {
		this->cameraPos = position;
		RecalculateViewMatrix();
		RecalculateVPMatrix();
	}

	float GetCameraSize2D() { return size2D; }
	float GetPitch() { return pitch; }
	float GetYaw() { return yaw; }
	float GetRoll() { return roll; }
	glm::vec3 GetCameraPos() { return cameraPos; }
	glm::vec3 GetCameraUp() { return cameraUp; }
	glm::vec3 GetCameraFront() { return cameraFront; }

	glm::mat4 GetViewMatrix() { return viewMatrix; }
	glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	glm::mat4 GetVPMatrix() { return vpMatrix; }

private:
	CameraType cameraType;

	float yaw;
	float pitch;
	float roll;
	float fov; //3D
	float size2D;
	float nearClip;
	float farClip;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 vpMatrix;

	void RecalculateViewMatrix();
	void RecalculateProjectionMatrix();
	void RecalculateVPMatrix();

	void FramebufferSizeCallback(int windowWidth, int windowHeight);
};