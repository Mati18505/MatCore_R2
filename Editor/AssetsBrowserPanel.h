#pragma once
#include "MatCore.h"
#include <filesystem>
#include <map>
#include "PlatformUtils.h"

class AssetsBrowserPanel {
public:
	AssetsBrowserPanel();

	void Render();
private:
	std::filesystem::path currentDirectory;
	std::map<std::string, std::shared_ptr<MatCore::Texture2D>> icons;
	std::map<std::string, std::shared_ptr<MatCore::Texture2D>> filesImagesCache;

	struct File {
		bool isDirectory;
		std::string filenameString;
		std::shared_ptr<MatCore::Texture2D> icon;
		std::filesystem::path path;
		std::string fileExtension;
	};
	std::vector<File> files;

	void UpdateFilesList();
	void RenderFilesList();

	const float padding = 16.f;
	const float thumbnailSize = 128.f;
};

