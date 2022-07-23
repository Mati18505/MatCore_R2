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
};

