#pragma once
#include <entt.hpp>
#include "Log.h"

namespace MatCore {
	class Scene;	
	class Entity {
	public:
		Entity() : entityHandle(entt::null), scene(nullptr) {}
		Entity(entt::entity entity, Scene* scene) :entityHandle(entity), scene(scene) {} //TODO: schowaæ przed klientem
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			if (!scene->entitiesRegistry.valid(*this)) {
				LOG_CORE_CRITICAL("AddComponent: Entity was destroyed!");
				assert("AddComponent: Entity was destroyed!");
			}
			if (HasComponent<T>()) {
				LOG_CORE_WARN("AddComponent: Entity already has component!");
				return GetComponent<T>();
			}
			return scene->entitiesRegistry.emplace<T>(entityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent() {
			if (!scene->entitiesRegistry.valid(*this)) {
				LOG_CORE_CRITICAL("GetComponent: Entity was destroyed!");
				assert("GetComponent: Entity was destroyed!");
			}
			if (!HasComponent<T>()) {
				LOG_CORE_CRITICAL("GetComponent: Entity does not have component!");
				assert("Entity does not have component!");
			}
			return scene->entitiesRegistry.get<T>(entityHandle);
		}

		template<typename T>
		bool HasComponent() {
			if (!scene->entitiesRegistry.valid(*this)) {
				LOG_CORE_WARN("HasComponent: Entity was destroyed!");
				return false;
			}

			return scene->entitiesRegistry.all_of<T>(entityHandle);
		}

		template<typename T>
		void RemoveComponent() {
			if (!scene->entitiesRegistry.valid(*this)) {
				LOG_CORE_WARN("RemoveComponent: Entity was destroyed!");
				return;
			}
			scene->entitiesRegistry.remove<T>(entityHandle);
		}

		static Entity Null() { return Entity(); }

		operator bool() const { return this->entityHandle != entt::null; }
		operator entt::entity() const { return entityHandle; }
		operator int() const { return (int)entityHandle; }
		bool operator ==(Entity other) const { return other.entityHandle == this->entityHandle; }//TODO: dodaæ do sprawdzania scene
		bool operator !=(Entity other) const { return !(other == *this); }

	private:
		entt::entity entityHandle;
		Scene* scene;
	};
}
