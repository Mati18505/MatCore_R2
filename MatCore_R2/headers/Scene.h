#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt.hpp>
#include <utility>
#include <optional>

namespace MatCore {
	class SceneCamera;
	class Camera;
	class Entity;
	namespace MeshRenderer {
		void OnConstruct(entt::registry&, entt::entity entity);
		void OnDestroy(entt::registry&, entt::entity entity);
	}

	class Scene {
	public:
		Scene();
		virtual ~Scene();
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		Entity CreateEntity(std::string name = "");
		Entity CreateEntity(std::string name, Entity parent);
		void DestroyEntity(Entity entity);

		std::pair<SceneCamera*, Entity> GetMainRuntimeCamera();
		std::optional<Camera> GetMainCamera();
	private:
		bool runtime = true;

		void DestroyEntityChildrens(Entity entity);
		void EraseEntityFromHisParent(Entity entity);
		friend class Entity;
		friend class Renderer;
		friend class TransformSystem;
		friend class Application;
		void BaseUpdate();
		void FrameBufferSizeCallback(int width, int height);

		friend void MeshRenderer::OnConstruct(entt::registry&, entt::entity entity);
		friend void MeshRenderer::OnDestroy(entt::registry&, entt::entity entity);
	protected:
		entt::registry entitiesRegistry;

		//void OnEditorUpdate();
		void OnRuntimeUpdate();
	};
}