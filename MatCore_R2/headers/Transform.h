#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace MatCore {
	//TODO: optymalizacja: dirtyFlag
	struct Transform {
	public:
		Transform() = default;
		~Transform() = default;

		//lokalne
		glm::vec3 position { 0, 0, 0 };
		glm::vec3 rotation { 0, 0, 0 };
		glm::vec3 scale { 1, 1, 1 };

		glm::mat4 GetGlobalModelMatrix() { return globalModelMatrix; }
		glm::vec3 GetLocalForwardVector() {
			glm::vec3 front;
			front.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
			front.y = sin(glm::radians(rotation.x));
			front.z = cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
			return glm::normalize(front);
		}

	private:
		friend class TransformSystem;

		//globalne
		glm::mat4 globalModelMatrix = glm::mat4(1.f);
	};
}