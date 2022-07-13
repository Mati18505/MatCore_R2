#pragma once
#include "Application.h"
#include "Log.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "Transform.h"
#include "material.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "Entity.h"
#include "Log.h"
#include "Model.h"
#include "Texture.h"

using namespace MatCore;
class EditorScene : public Scene
{
public:
	EditorScene();
	~EditorScene();
	void Start();
	void Update();

private:

};