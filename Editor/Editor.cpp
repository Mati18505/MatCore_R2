#include "Editor.h"
#include 

using namespace MatCore;

Scene* Application::ApplicationStart() {
	return new EditorScene();
}

EditorScene::EditorScene()
{
}

EditorScene::~EditorScene()
{
	delete this->camera;
}

void EditorScene::Start()
{
}

void EditorScene::Update()
{
}
