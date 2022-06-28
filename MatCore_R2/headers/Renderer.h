#pragma once

struct MeshRenderer;
class Renderer {
public:
	Renderer();
	~Renderer();
	void RenderScene();
private:
	MeshRenderer* testMeshRenderer;
	void RenderMesh(MeshRenderer* meshRenderer);
};