#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MatCore {
	class Camera {
	public:
		Camera() : viewMatrix(glm::mat4(1.f)), projectionMatrix(glm::mat4(1.f)) {}
		Camera(const glm::mat4& view, const glm::mat4& projection) : viewMatrix(view), projectionMatrix(projection) {}
		virtual ~Camera() {};

		const glm::mat4& GetProjection() const { return projectionMatrix; }
		const glm::mat4& GetView() const { return viewMatrix; }
	protected:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
	};
}
