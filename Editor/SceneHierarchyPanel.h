#pragma once
#include "MatCore.h"

class EditorScene;
struct ImVec2;
class SceneHierarchyPanel {
public:
	SceneHierarchyPanel() : selectedEntity(MatCore::Entity::Null()) {}
	void Render(EditorScene* scene);
	MatCore::Entity GetSelectedEntity() { return selectedEntity; }
private:
	void DrawEntityNode(MatCore::Entity entity, EditorScene* scene); 
	void DrawInspectorComponents(MatCore::Entity entity); 

	void DrawTagComponent(MatCore::Entity entity);
	void DrawAddComponentButton(ImVec2 contentRegionAvalible);
	MatCore::Entity selectedEntity;
};