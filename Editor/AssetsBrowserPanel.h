#pragma once
#include "MatCore.h"
#include <filesystem>
#include <map>
#include <string>
#include "PlatformUtils.h"

class AssetsBrowserPanel {
public:
	AssetsBrowserPanel();

	void Render();
private:
	std::filesystem::path currentDirectory;
	std::map<std::string, MatCore::Resource<MatCore::Texture2D>> icons;
	std::map<std::string, MatCore::Resource<MatCore::Texture2D>> filesImagesCache;

	struct File {
		bool isDirectory;
		std::string filenameString;
		MatCore::Resource<MatCore::Texture2D> icon;
		std::filesystem::path path;
		std::string fileExtension;
	};
	std::vector<File> files;

	void UpdateFilesList();
	void RenderFilesList();

	const float padding = 16.f;
	const float thumbnailSize = 128.f;
};

