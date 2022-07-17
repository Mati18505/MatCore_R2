#include "SceneHierarchyPanel.h"
#include "Dependece/ImGUI/imgui.h"
#include "Editor.h"

void SceneHierarchyPanel::Render(EditorScene* scene) {
	using namespace MatCore;
	//ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);

	ImGui::Begin("Hierarchia sceny");

	scene->entitiesRegistry.each([&](auto entityHandler)
	{
		Entity entity(entityHandler, scene);
		if (entity.GetComponent<InheritanceComponent>().parentEntity == Entity::Null())
			DrawEntityNode(entity, scene);
	});

	//Jeœli klikniêto w puste miejsce w oknie
	if (ImGui::IsMouseDown(ImGuiMouseButton_::ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
		selectedEntity = {};

	ImGui::End();

	ImGui::Begin("Inspektor");
	if(selectedEntity)
		DrawInspector(selectedEntity);
	ImGui::End();
}

void SceneHierarchyPanel::DrawEntityNode(Entity entity, EditorScene* scene)
{
	using namespace MatCore;
	ImGuiTreeNodeFlags flags = ((selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	auto& tag = entity.GetComponent<TagComponent>();
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entt::entity)entity, flags, tag.Tag().c_str());

	if (ImGui::IsItemClicked())
	{
		selectedEntity = entity;
	}
	if (opened) {
		for (Entity child : entity.GetComponent<InheritanceComponent>().childEntities)
			DrawEntityNode(child, scene);
		ImGui::TreePop();
	}
}

void SceneHierarchyPanel::DrawInspector(MatCore::Entity entity)
{
	if (entity.HasComponent<TagComponent>()) {
		if (ImGui::TreeNodeEx((void*)typeid(TagComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Tag"))
		{
			std::string& tag = entity.GetComponent<TagComponent>().Tag();

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));

			strcpy_s(buffer, sizeof(buffer), tag.c_str());

			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
				tag = std::string(buffer);

			ImGui::TreePop();
		}
	}
	ImGui::Separator();
	if (entity.HasComponent<Transform>()) {
		if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) 
		{
			auto& transform = entity.GetComponent<Transform>();
			ImGui::DragFloat3("Position", &transform.position[0], 0.1f);
			ImGui::DragFloat3("Rotation", &transform.rotation[0], 0.1f);
			ImGui::DragFloat3("Scale", &transform.scale[0], 0.1f);

			ImGui::TreePop();
		}
		
	}
	ImGui::Separator();
	if (entity.HasComponent<InheritanceComponent>()) {
		if (ImGui::TreeNodeEx((void*)typeid(InheritanceComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Dziedziczenie"))
		{
			ImGui::Text("Dzieci: ");
			for (Entity e : entity.GetComponent<InheritanceComponent>().childEntities)
			{
				ImGui::Text(e.GetComponent<TagComponent>().Tag().c_str());
			}
			ImGui::Separator();
			ImGui::Text("Rodzic: ");
			if (Entity parent = entity.GetComponent<InheritanceComponent>().parentEntity) {
				ImGui::Text(parent.GetComponent<TagComponent>().Tag().c_str());
			}

			ImGui::TreePop();
		}
	}
	ImGui::Separator();
	if (entity.HasComponent<Material>()) {
		if (ImGui::TreeNodeEx((void*)typeid(Material).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, u8"Materia³"))
		{
			auto& material = entity.GetComponent<Material>();
			ImGui::Text("Albedo");
			if (entity.GetComponent<Material>().albedo != nullptr) {
				std::shared_ptr<Texture2D> texture = material.albedo;
				ImGui::Image(texture->GetRawHandle(), { 128.f, 128.f });
			}
			
			ImGui::TreePop();
		}
	}

}
