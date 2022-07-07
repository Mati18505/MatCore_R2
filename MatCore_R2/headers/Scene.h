#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt.hpp>

class Camera;

class Scene {
public:
	Scene();
	~Scene();
	virtual void Start() = 0;
	virtual void Update() = 0;

	entt::registry entitiesRegistry;

	//TODO: przenieœæ do Editor
	Camera* camera;
private:
};