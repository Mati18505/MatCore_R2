#include "SceneHierarchyPanel.h"
#include "Dependece/ImGUI/imgui.h"
#include "Dependece/ImGUI/imgui_internal.h"
#include "Editor.h"

static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.f)
{
	ImGuiIO& io = ImGui::GetIO();
	auto boldFont = io.Fonts->Fonts[0];
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
	ImGui::PushFont(boldFont);
	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	
	ImGui::PushStyleColor(ImGuiCol_Button, { .2f, .7f, .2f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .3f, .8f, .3f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .2f, .7f, .2f, 1.f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	
	ImGui::PushStyleColor(ImGuiCol_Button, { .1f, .25f, .8f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .2f, .35f, .9f, 1.f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .1f, .25f, .8f, 1.f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Z", buttonSize))
		values.z = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f);
	ImGui::PopItemWidth();
	
	ImGui::PopStyleVar();

	ImGui::Columns(1);
	ImGui::PopID();
}

static void AttributeFloat(const std::string& label, float& value, float dragSpeed = 1.f, float columnWidth = 100.f) {
	ImGui::PushID(label.c_str());
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();
	ImGui::DragFloat("", &value, dragSpeed);
	ImGui::Columns(1);
	ImGui::PopID();
}

template<typename T>
static void DrawInspectorComponent(const char* componentName, MatCore::Entity entity, bool removable, std::function<void(T& component)> componentElements) {
	if (entity.HasComponent<T>()) {
		ImGui::PushID(typeid(T).hash_code());

		auto contentRegionAvalible = ImGui::GetContentRegionAvail();

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4, 4 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

		ImGui::Separator();	
		bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth 
			| ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding, componentName);

		ImGui::PopStyleVar(); 

		ImGui::SameLine(contentRegionAvalible.x - lineHeight * 0.5f);

		//Przycisk ...
		if (ImGui::Button("...", { lineHeight, lineHeight }))
		{
			ImGui::OpenPopup("ComponentSettings");
		}
		
		//Menu ...
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
			auto& component = entity.GetComponent<T>();
			componentElements(component);
			ImGui::TreePop();
		}

		if (removeComponent)
			entity.RemoveComponent<T>();

		ImGui::PopID();
	}
}

void SceneHierarchyPanel::Render(EditorScene* scene) {
	using namespace MatCore;
	//ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 250.f, 500.f });
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
			selectedEntity = scene->CreateEntity();
		}
		ImGui::EndPopup();
	}

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 450.f, 500.f });
	ImGui::Begin("Inspektor");
	if (selectedEntity) {
		DrawInspectorComponents(selectedEntity);
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

void SceneHierarchyPanel::DrawEntityNode(Entity entity, EditorScene* scene)
{
	using namespace MatCore;
	ImGuiTreeNodeFlags flags = ((selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow
		| ImGuiTreeNodeFlags_SpanAvailWidth;
	if (entity.GetComponent<InheritanceComponent>().childEntities.empty())
		flags |= ImGuiTreeNodeFlags_Leaf;

	auto& tag = entity.GetComponent<TagComponent>();
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entt::entity)entity, flags, tag.tag.c_str());

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
			selectedEntity = scene->CreateEntity("", entity);
		}
		ImGui::EndPopup();
	}

	if (opened) {
		for (Entity child : entity.GetComponent<InheritanceComponent>().childEntities)
			DrawEntityNode(child, scene);
		ImGui::TreePop();
	}
	if (entityDeleted) {
		//Jeœli wybrany entity jest usuwanym entity, lub jego dzieckiem: selectedEntity = NULL
		if (entity == selectedEntity)
			selectedEntity = Entity::Null();
		else {
			for (auto childEntity : entity.GetComponent<InheritanceComponent>().childEntities) {
				if (selectedEntity == childEntity)
				{
					selectedEntity = Entity::Null();
					break;
				}
			}
		}

		scene->DestroyEntity(entity);
	}
		
}

void SceneHierarchyPanel::DrawInspectorComponents(MatCore::Entity entity)
{
	auto contentRegionAvalible = ImGui::GetContentRegionAvail();
	DrawTagComponent(entity);

	DrawAddComponentButton(contentRegionAvalible);

	DrawInspectorComponent<Transform>("Transform", entity, false, [&](Transform& transform) {
		DrawVec3Control("Position", transform.position, 0.f);
		DrawVec3Control("Rotation", transform.rotation, 0.f);
		DrawVec3Control("Scale", transform.scale, 1.f);
	});
	
	DrawInspectorComponent<InheritanceComponent>("Dziedziczenie", entity, false, [&](InheritanceComponent&)
	{
		ImGui::Text("Dzieci: ");
		for (Entity e : entity.GetComponent<InheritanceComponent>().childEntities)
		{
			ImGui::Text(e.GetComponent<TagComponent>().tag.c_str());
		}
		ImGui::Separator();
		ImGui::Text("Rodzic: ");
		if (Entity parent = entity.GetComponent<InheritanceComponent>().parentEntity) {
			ImGui::Text(parent.GetComponent<TagComponent>().tag.c_str());
		}
	});
	
	DrawInspectorComponent<Material>(u8"Materia³", entity, true, [&](Material& material) {
		ImGui::Text(("ShaderID: " + std::to_string(material.shaderID)).c_str());
		ImGui::Text("Albedo");
		if (entity.GetComponent<Material>().albedo != nullptr) {
			std::shared_ptr<Texture2D> texture = material.albedo;
			ImGui::Image(texture->GetRawHandle(), { 128.f, 128.f });
		}
	});

	DrawInspectorComponent<MeshComponent>(u8"Mesh", entity, true, [&](MeshComponent& mesh) {
		ImGui::Text(("Vertices: " + std::to_string(mesh.mesh.GetVertices()->size())).c_str());
		ImGui::Text(("Triangles: " + std::to_string(mesh.mesh.GetTriangles()->size())).c_str());
	});
	
	DrawInspectorComponent<CameraComponent>(u8"Camera", entity, true, [&](CameraComponent& camera) {
		{
			int current = (int)camera.camera.cameraType;
			if(ImGui::Combo("Camera type", &current,"Orthographic\0Perspective"))
				camera.camera.cameraType = SceneCamera::CameraType(current);
		}
		ImGui::Checkbox("primary", &camera.primary);
		AttributeFloat("FOV", camera.camera.fov, .1f);
		AttributeFloat("Size 2D", camera.camera.size2D, .01f);
		AttributeFloat("Near clip", camera.camera.nearClip, .01f);
		AttributeFloat("Far clip", camera.camera.farClip);
	});

}

void SceneHierarchyPanel::DrawTagComponent(MatCore::Entity entity)
{
	std::string& tag = entity.GetComponent<TagComponent>().tag;

	char buffer[256];
	memset(buffer, 0, sizeof(buffer));

	strcpy_s(buffer, sizeof(buffer), tag.c_str());

	if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
		tag = std::string(buffer);
}

void SceneHierarchyPanel::DrawAddComponentButton(ImVec2 contentRegionAvalible)
{
	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImGui::SameLine(contentRegionAvalible.x - lineHeight * 0.5f);
	if (ImGui::Button("+", { lineHeight, lineHeight }))
		ImGui::OpenPopup("AddComponent");
	//TODO: zautomatyzowaæ dodawanie elementów do tej listy
	if (ImGui::BeginPopup("AddComponent"))
	{
		if (!selectedEntity.HasComponent<Material>()) {
			if (ImGui::MenuItem("Material")) {
				selectedEntity.AddComponent<Material>();
				ImGui::CloseCurrentPopup();
			}
		}
		if (!selectedEntity.HasComponent<MeshComponent>()) {
			if (ImGui::MenuItem("Mesh Component")) {
				selectedEntity.AddComponent<MeshComponent>(Mesh::Cone(360, 2, 4));
				ImGui::CloseCurrentPopup();
			}
		}
		if (!selectedEntity.HasComponent<CameraComponent>()) {
			if (ImGui::MenuItem("Camera Component")) {
				selectedEntity.AddComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}
		}
		
		ImGui::EndPopup();
	}
}
