#pragma once
#include <entt.hpp>
namespace MatCore {
	class Application;
	extern Application* applicationP;//= applicationP z pliku MatCore_R2.cpp

	struct MeshComponent;
	struct Transform;
	struct Material;
	class Renderer {
	public:
		Renderer();
		~Renderer();
		void RenderScene();
	private:

	};

	namespace MeshRenderer {
		void OnConstruct(entt::registry&, entt::entity entity);
		void OnDestroy(entt::registry&, entt::entity entity);
		void Init(MeshComponent& meshComponent);
		void RenderMesh(MeshComponent& meshRenderer, Transform& transform, Material& material);
		void DeInit(MeshComponent& meshComponent);
	}
}