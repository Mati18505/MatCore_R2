#include "AssetsBrowserPanel.h"
#include "Dependece/ImGUI/imgui.h"
#include "Dependece/ImGUI/imgui_internal.h"
#include "Editor.h"

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
	ImGui::Begin("Assets browser");

	if (currentDirectory != std::filesystem::path(assetsPath)) {
		if (ImGui::Button("<-"))
			currentDirectory = currentDirectory.parent_path();
	}
	ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Open in file explorer").x);
	if (ImGui::Button("Open in file explorer")) {
		LOG_INFO("Opening {0} in file explorer", currentDirectory);
		FileDialog::OpenFile("All files (*.*)\0*.*\0"); //TODO: zast¹piæ file explorerem
	}
		

	static float padding = 16.f;
	static float thumbnailSize = 128.f;
	float cellSize = thumbnailSize + padding;

	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = int(panelWidth / cellSize);
	if (columnCount < 1)
		columnCount = 1;

	ImGui::Columns(columnCount, 0, false);
	for (auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
	{
		const auto& path = directoryEntry.path();

		auto relativePath = std::filesystem::relative(path, assetsPath);
		std::string filenameString = relativePath.filename().string();
		ImGui::PushID(filenameString.c_str());

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
				filesImagesCache.emplace(path.string(), std::make_unique<Texture2D>(path.string().c_str()));
			}
			icon = filesImagesCache.at(path.string());
		}
		else
			icon = icons.at("empty");

		

		ImGui::PushStyleColor(ImGuiCol_Button, {});
		ImGui::ImageButton(icon->GetRawHandle(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }); // TODO: u¿yæ czcionki fontello zamiast image
		ImGui::PopStyleColor();

		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			if (directoryEntry.is_directory()) {
				currentDirectory /= path.filename();
			}
			else
			{
				std::cout << system((path.string()).c_str()); //mo¿e nie dzia³aæ na innych wersjach windows
				if (fileExtension == ".txt")
					;
			}	
		}
		CenteredText(filenameString.c_str(), thumbnailSize);
		
		
		ImGui::NextColumn();
		ImGui::PopID();
	}
	ImGui::Columns(1);
	ImGui::End();
}