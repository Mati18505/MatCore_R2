#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt.hpp>

class Mesh;
class Camera;

class Scene {
public:
	Scene() :camera(nullptr), entity(entt::null) {}
	~Scene();
	void Start();
	void Update();

	entt::registry entitiesRegistry;

	//TODO: przenieœæ do Editor
	Camera* camera;
private:
	entt::entity entity;
	double lastXMousePos{ 0 }, lastYMousePos{ 0 };
};