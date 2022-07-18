#include "SceneHierarchyPanel.h"
#include "Dependece/ImGUI/imgui.h"
#include "Dependece/ImGUI/imgui_internal.h"
#include "Editor.h"

static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.f)
{
	ImGui::PushID(label.c_str()); //uwaga: label nie mo¿e siê powtórzyæ

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.f, lineHeight };


	ImGui::PushStyleColor(ImGuiCol_Button, { .8f, .1f, .15f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .9f, .2f, .2f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .8f, .1f, .15f, 1.f });
	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	
	ImGui::PushStyleColor(ImGuiCol_Button, { .2f, .7f, .2f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .3f, .8f, .3f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .2f, .7f, .2f, 1.f });
	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	
	ImGui::PushStyleColor(ImGuiCol_Button, { .1f, .25f, .8f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .2f, .35f, .9f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .1f, .25f, .8f, 1.f });
	if (ImGui::Button("Z", buttonSize))
		values.z = resetValue;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f);
	ImGui::PopItemWidth();
	
	ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();
}

template<typename T>
static void DrawInspectorComponent(const char* componentName, MatCore::Entity entity, bool removable, std::function<void(void)> componentElements) {
	if (entity.HasComponent<T>()) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4, 4 });
		bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, componentName);
		ImGui::SameLine(ImGui::GetWindowWidth() - 25.f);
		if (ImGui::Button("+"))
		{
			ImGui::OpenPopup("ComponentSettings");
		}
		ImGui::PopStyleVar();

		bool removeComponent = false;
		if (ImGui::BeginPopup("ComponentSettings"))
		{
			if (removable) {
				if (ImGui::MenuItem(u8"Usuñ komponent"))
					removeComponent = true;
			}

			ImGui::EndPopup();
		}

		if(open)
		{
			componentElements();
			ImGui::TreePop();
		}

		if (removeComponent)
			entity.RemoveComponent<T>();

		ImGui::Separator();
	}
}

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

	//klikniêto w pust¹ przestrzeñ
	if (ImGui::BeginPopupContextWindow(0, 1, false)) 
	{
		if (ImGui::MenuItem(u8"Stwórz pusty obiekt")) {
			scene->CreateEntity();
		}
		ImGui::EndPopup();
	}

	ImGui::End();

	ImGui::Begin("Inspektor");
	if (selectedEntity) {
		DrawInspectorComponents(selectedEntity);
		if (ImGui::Button("Dodaj komponent"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent")) 
		{
			if (ImGui::MenuItem("Material")) {
				selectedEntity.AddComponent<Material>();
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Mesh Component")) {
				selectedEntity.AddComponent<MeshComponent>(Mesh::Cone(360, 2, 4));
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
		
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

	//klikniêto w entity
	bool entityDeleted = false;
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem(u8"Usuñ obiekt")) {
			entityDeleted = true;
		}
		if (ImGui::MenuItem(u8"Stwórz dziecko")) {
			scene->CreateEntity("", entity);
		}
		ImGui::EndPopup();
	}

	if (opened) {
		for (Entity child : entity.GetComponent<InheritanceComponent>().childEntities)
			DrawEntityNode(child, scene);
		ImGui::TreePop();
	}
	if (entityDeleted) {
		scene->DestroyEntity(entity);
		if (entity == selectedEntity)
			selectedEntity = Entity::Null();
	}
		
}

void SceneHierarchyPanel::DrawInspectorComponents(MatCore::Entity entity)
{
	DrawInspectorComponent<TagComponent>("Tag", entity, false, [&]()
	{
		std::string& tag = entity.GetComponent<TagComponent>().Tag();

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));

		strcpy_s(buffer, sizeof(buffer), tag.c_str());

		if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			tag = std::string(buffer);
	});

	DrawInspectorComponent<Transform>("Transform", entity, false, [&]() {
		auto& transform = entity.GetComponent<Transform>();
		DrawVec3Control("Position", transform.position, 0.f);
		DrawVec3Control("Rotation", transform.rotation, 0.f);
		DrawVec3Control("Scale", transform.scale, 1.f);
	});
	
	DrawInspectorComponent<InheritanceComponent>("Dziedziczenie", entity, false, [&]() 
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
	});
	
	DrawInspectorComponent<Material>(u8"Materia³", entity, true, [&]() {
		auto& material = entity.GetComponent<Material>();
		ImGui::Text("Albedo");
		if (entity.GetComponent<Material>().albedo != nullptr) {
			std::shared_ptr<Texture2D> texture = material.albedo;
			ImGui::Image(texture->GetRawHandle(), { 128.f, 128.f });
		}
	});

}
