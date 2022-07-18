#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace MatCore {
	struct Transform {
	public:
		Transform() = default;
		~Transform() = default;

		glm::vec3 position { 0, 0, 0 };
		glm::vec3 rotation { 0, 0, 0 };
		glm::vec3 scale { 1, 1, 1 };

		glm::mat4 GetModelMatrix();

	private:
		glm::mat4 modelMatrix = glm::mat4(1.f);

		void UpdateModelMatrix();
	};
}