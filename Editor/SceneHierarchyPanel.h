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
	void DrawInspectorComponents(EditorScene& scene, MatCore::Entity entity);

	void DrawTagComponent(MatCore::Entity entity);
	void DrawAddComponentButton(EditorScene& scene, ImVec2 contentRegionAvalible);

	void MaterialTextureAcceptDragDrop(MatCore::Material& material);
	MatCore::Entity selectedEntity;
};