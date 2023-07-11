#pragma once
#include <entt.hpp>
namespace MatCore {
	class Application;
	extern Application* applicationP;//= applicationP z pliku MatCore_R2.cpp

	struct MeshComponent;
	class Camera;
	struct Transform;
	struct Material;
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void RenderScene();
		unsigned int Vertices() { return vertices; }
		unsigned int Triangles() { return triangles; }
		unsigned int DrawCalls() { return drawCalls; }
	private:
		unsigned int vertices, triangles, drawCalls;
	};

	namespace MeshRenderer {
		void RenderMesh(MeshComponent& meshRenderer, Transform& transform, Material& material, Camera& camera);
	}
}