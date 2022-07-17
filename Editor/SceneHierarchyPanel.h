#pragma once
#include "MatCore.h"

class EditorScene;
class SceneHierarchyPanel {
public:
	SceneHierarchyPanel() : selectedEntity(MatCore::Entity::Null()) {}
	void Render(EditorScene* scene);
private:
	void DrawEntityNode(MatCore::Entity entity, EditorScene* scene); 
	void DrawInspector(MatCore::Entity entity); 
	MatCore::Entity selectedEntity;
};