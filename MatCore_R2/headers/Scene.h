#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt.hpp>
namespace MatCore {
	class Camera;
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

		//TODO: przenieœæ do Editor
		Camera* camera;
	private:
		friend class Entity;
		friend class Renderer;
		friend void MeshRenderer::OnConstruct(entt::registry&, entt::entity entity);
		friend void MeshRenderer::OnDestroy(entt::registry&, entt::entity entity);
		entt::registry entitiesRegistry;
	};
}