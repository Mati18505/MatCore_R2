#pragma once
#include "Camera.h"

namespace MatCore {
	class Transform;
	class SceneCamera : public Camera {
	public:
		SceneCamera() = default;

		enum class CameraType {
			orthographic,
			perspective
		};

		CameraType cameraType = CameraType::perspective;
		float fov = 90;
		float size2D = 1.f;
		float nearClip = 0.1f;
		float farClip = 1000.f;
		glm::vec2 viewportSize{ 0, 0 }; //jeœli 0 = application.windowSize TODO: zast¹piæ pobieraniem wielkoœci z render target
	private:
		void RecalculateViewMatrix(Transform& transform);
		void RecalculateProjectionMatrix(int width, int height);
		
		friend class Scene;
	};
}