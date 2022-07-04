#pragma once
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
	void Init(MeshComponent& meshRenderer);
	void RenderMesh(MeshComponent& meshRenderer, Transform& transform, Material& material);
	void DeInit(MeshComponent& meshRenderer);
}