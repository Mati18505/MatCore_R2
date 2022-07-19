#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MatCore {
	struct Transform;
	class Entity;
	class TransformSystem {
	public:
		static void UpdateAllTransforms();
	private:
		static void UpdateSelfAndChild(Entity entity);
		static glm::mat4 GetLocalModelMatrix(Transform& transform);
	};
}