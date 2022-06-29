#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Application;
extern Application* applicationP;//= applicationP z pliku MatCore_R2.cpp

class Mesh;
struct Transform;
class Renderer {
public:
	Renderer();
	~Renderer();
	void RenderScene();
private:
	
	unsigned int testShaderID;
};

namespace MeshRenderer {
	void Init(Mesh& meshRenderer);
	void RenderMesh(Mesh& meshRenderer, Transform& transform, unsigned int shaderID);
	void DeInit(Mesh& meshRenderer);
}