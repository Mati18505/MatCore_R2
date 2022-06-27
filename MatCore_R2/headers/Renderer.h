#pragma once

class MeshRenderer;
class Renderer {
public:
	Renderer();
	void RenderScene();
private:
	MeshRenderer* testMeshRenderer;
	void RenderMesh(MeshRenderer* meshRenderer);
};