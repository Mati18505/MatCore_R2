#pragma once
class Application;
extern Application* applicationP;//= applicationP z pliku MatCore_R2.cpp

class Mesh;
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
	void Init(Mesh& meshRenderer);
	void RenderMesh(Mesh& meshRenderer, Transform& transform, Material& material);
	void DeInit(Mesh& meshRenderer);
}