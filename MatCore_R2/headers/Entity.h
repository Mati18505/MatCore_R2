#pragma once
#include <entt.hpp>

namespace MatCore {
	class Scene;
	class Entity {
	public:
		Entity(Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			if (HasComponent<T>()) {
				LOG_CORE_WARN("AddComponent: Entity already has component!");
				return GetComponent<T>();
			}
			return scene->entitiesRegistry.emplace<T>(entityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent() {
			if (!HasComponent<T>()) {
				LOG_CORE_CRITICAL("GetComponent: Entity does not have component!");
				assert("Entity does not have component!");
			}
			return scene->entitiesRegistry.get<T>(entityHandle);
		}

		template<typename T>
		bool HasComponent() {
			return scene->entitiesRegistry.all_of<T>(entityHandle);
		}

		template<typename T>
		void RemoveComponent() {
			scene->entitiesRegistry.remove<T>(entityHandle);
		}

		operator entt::entity() const { return entityHandle; }

	private:
		entt::entity entityHandle;
		Scene* scene;
	};
}
