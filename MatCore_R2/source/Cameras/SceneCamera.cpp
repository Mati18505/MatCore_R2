#include "Cameras/SceneCamera.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MatCore {
	void MatCore::SceneCamera::RecalculateProjectionMatrix(int width, int height) {
		glm::vec2 size;
		if (viewportSize.y == 0)
			size = { width, height };
		else
			size = { viewportSize.x, viewportSize.y };

		if (this->cameraType == CameraType::perspective)
			projectionMatrix = glm::perspective(glm::radians(fov), (float)size.x / size.y, nearClip, farClip);
		else
			projectionMatrix = glm::ortho(-(size.x / 2) * size2D, size.x / 2 * size2D, -(size.y / 2 * size2D), size.y / 2 * size2D, nearClip, farClip);
	}

	void MatCore::SceneCamera::RecalculateViewMatrix(Transform& transform) {
		glm::vec3 cameraFront = transform.GetLocalForwardVector();

		glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), transform.GetLocalForwardVector());
		glm::vec3 cameraUp = glm::normalize(glm::mat3(rollMatrix) * glm::vec3(0, 1, 0));

		this->viewMatrix = glm::lookAt(transform.position, transform.position + cameraFront, cameraUp);
	}
}
