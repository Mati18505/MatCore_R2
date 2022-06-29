#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh;

class Scene {
public:
	Scene() = default;
	~Scene() = default;
	void Start();
	void Update();
	//TODO: zrobiæ prywatne
	Mesh* testMesh;
	
	glm::mat4 modelMatrix, VPMatrix, mvpMatrix;
private:
	
};