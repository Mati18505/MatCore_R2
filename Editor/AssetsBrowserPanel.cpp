#include "AssetsBrowserPanel.h"
#include "Dependece/ImGUI/imgui.h"
#include "Dependece/ImGUI/imgui_internal.h"
#include "Editor.h"
#include <shellapi.h>

static void CenteredText(const char* text, float avalibleSizeX) {
	float textWidth = ImGui::CalcTextSize(text).x;
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (avalibleSizeX - textWidth) * 0.5f);
	ImGui::Text(text);
}

static const std::filesystem::path assetsPath = "Assets";

AssetsBrowserPanel::AssetsBrowserPanel()
	:currentDirectory(assetsPath)
{
	icons.emplace<std::string, std::shared_ptr<Texture2D>>("folder", std::make_shared<Texture2D>("./Resources/AssetsBrowser/folderIcon.png"));
	icons.emplace<std::string, std::shared_ptr<Texture2D>>("text", std::make_shared<Texture2D>("./Resources/AssetsBrowser/text.jpg"));
	icons.emplace<std::string, std::shared_ptr<Texture2D>>("fbx", std::make_shared<Texture2D>("./Resources/AssetsBrowser/FBX.png"));
	icons.emplace<std::string, std::shared_ptr<Texture2D>>("obj", std::make_shared<Texture2D>("./Resources/AssetsBrowser/OBJ.png"));
	icons.emplace<std::string, std::shared_ptr<Texture2D>>("empty", std::make_shared<Texture2D>("./Resources/AssetsBrowser/text.jpg"));
}

void AssetsBrowserPanel::Render() {
	static float timer;
	ImGui::Begin("Assets browser");

	if (currentDirectory != std::filesystem::path(assetsPath)) {
		if (ImGui::Button("<-"))
			currentDirectory = currentDirectory.parent_path();
	}
	ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Open in file explorer").x);
	if (ImGui::Button("Open in file explorer")) {
		ShellExecute(NULL, "explore", (currentDirectory.string()).c_str(), NULL, NULL, SW_SHOWNORMAL);
	}
	
	if (timer > 500)
	{
		UpdateFilesList();
		timer = 0;
	}
	timer += applicationP->deltaTime;

	RenderFilesList();
	
	ImGui::End();
}

void AssetsBrowserPanel::UpdateFilesList()
{
	files.clear();
	for (auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
	{
		File file;

		const auto& path = directoryEntry.path();

		auto relativePath = std::filesystem::relative(path, assetsPath);
		file.filenameString = relativePath.filename().string();
		

		std::string fileExtension = relativePath.filename().extension().string();

		std::shared_ptr<Texture2D> icon;
		if (directoryEntry.is_directory())
			icon = icons.at("folder");
		else if (fileExtension == ".txt")
			icon = icons.at("text");
		else if (fileExtension == ".obj")
			icon = icons.at("obj");
		else if (fileExtension == ".fbx")
			icon = icons.at("fbx");
		else if (fileExtension == ".png")
		{
			auto i = filesImagesCache.find(path.string());
			if (i == filesImagesCache.end())
			{
				//TODO: ³adowaæ teksturê w niskiej rozdzielczoœci (rozdzielczoœci kafelka) aby nie trwa³o to zbyt d³ugo
				//TODO: nie ³adowaæ wszystkich na raz tylko kilka na klatkê
				filesImagesCache.emplace(path.string(), std::make_shared<Texture2D>(path.string().c_str()));
			}
			icon = filesImagesCache.at(path.string());
		}
		else
			icon = icons.at("empty");

		file.icon = icon;
		file.path = path;
		file.fileExtension = fileExtension;
		file.isDirectory = directoryEntry.is_directory();
		files.push_back(file);
	}
	
}

void AssetsBrowserPanel::RenderFilesList()
{
	float cellSize = thumbnailSize + padding;
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = int(panelWidth / cellSize);
	if (columnCount < 1)
		columnCount = 1;

	ImGui::Columns(columnCount, 0, false);

	for (File& file : files) 
	{
		ImGui::PushID(file.filenameString.c_str());
		ImGui::PushStyleColor(ImGuiCol_Button, {});
		ImGui::ImageButton(file.icon->GetRawHandle(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }); // TODO: u¿yæ czcionki fontello zamiast image
		
		if (ImGui::BeginDragDropSource()) {
			std::string filePath = file.path.string();
			const char* itemPath = filePath.c_str();
			ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (strlen(itemPath) + 1) * sizeof(char));
			ImGui::Text(itemPath);
			ImGui::EndDragDropSource();
		}

		ImGui::PopStyleColor();

		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			if (file.isDirectory) {
				currentDirectory /= file.path.filename();
			}
			else
			{
				ShellExecute(NULL, "open", (file.path.string()).c_str(), NULL, NULL, SW_SHOWNORMAL);
				if (file.fileExtension == ".txt")
					;
			}
		}
		CenteredText(file.filenameString.c_str(), thumbnailSize);
		ImGui::NextColumn();
		ImGui::PopID();
	}

	ImGui::Columns(1);
}
