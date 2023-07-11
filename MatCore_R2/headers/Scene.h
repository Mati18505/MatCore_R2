#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt.hpp>
#include <optional>
#include "SceneRenderer.h"

namespace MatCore {
	class SceneCamera;
	class Camera;
	class Entity;
	class Event;

	class Scene {
	public:
		Scene();
		virtual ~Scene();
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void OnEvent(Event& e) = 0;

		Entity CreateEntity(std::string name = "");
		Entity CreateEntity(std::string name, Entity parent);
		void DestroyEntity(Entity entity);

		Entity GetMainRuntimeCameraEntity();
		virtual std::optional<Camera> GetMainCamera();
		entt::registry& GetEntities() {
			return entitiesRegistry;
		}
	private:
		void DestroyEntityChildrens(Entity entity);
		void EraseEntityFromHisParent(Entity entity);
		friend class Entity;
		friend class TransformSystem;
		friend class Application;
		friend class SceneSerializer;
		void BaseUpdate();
		void FrameBufferSizeCallback(int width, int height);

		SceneRenderer sceneRenderer;
	protected:
		entt::registry entitiesRegistry;

		void OnRuntimeUpdate();
	};
}