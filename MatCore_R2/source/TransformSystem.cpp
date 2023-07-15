#include "pch.h"

#include "TransformSystem.h"
#include "MatCore.h"
extern MatCore::Application* applicationP;

namespace MatCore {
	void TransformSystem::UpdateAllTransforms() {
		auto view = applicationP->scene->entitiesRegistry.view<Transform>();
		for (auto entityH : view) {
			Entity entity(entityH, applicationP->scene);
			//if (t.IsDirty()) {
			if(entity.GetComponent<InheritanceComponent>().parentEntity == Entity::Null())
				UpdateSelfAndChild(entity);
			//}
		}
	}

	void TransformSystem::UpdateSelfAndChild(Entity entity) {
		auto& IC = entity.GetComponent<InheritanceComponent>();
		auto& transform = entity.GetComponent<Transform>();
		Entity parent = IC.parentEntity;
		if (parent)
			transform.globalModelMatrix = parent.GetComponent<Transform>().globalModelMatrix * GetLocalModelMatrix(transform);
		else
			transform.globalModelMatrix = GetLocalModelMatrix(transform);
		for (Entity child : IC.childEntities)
			UpdateSelfAndChild(child);
	}

	glm::mat4 TransformSystem::GetLocalModelMatrix(Transform& transform) {
		glm::mat4 modelMatrix(1.f);
		modelMatrix = glm::translate(modelMatrix, transform.position);

		modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.z), { 0, 0, 1 });
		modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.x), { 1, 0, 0 });
		modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.y), { 0, 1, 0 });

		modelMatrix = glm::scale(modelMatrix, transform.scale);
		return modelMatrix;
	}
}
