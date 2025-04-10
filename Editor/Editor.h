#pragma once
#include "MatCore.h"
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "SceneHierarchyPanel.h"
#include "AssetsBrowserPanel.h"

using namespace MatCore;

struct ImFontConfig;
typedef int ImGuiConfigFlags;

class EditorScene : public Scene
{
public:
	EditorScene();
	~EditorScene();
	void Start() override;
	void Update() override;
	void Render() override;
	void OnEvent(Event& e) override {};

private:
	friend class SceneHierarchyPanel;
	SceneHierarchyPanel hierarchyPanel;
	AssetsBrowserPanel assetsPanel;

	void SetupImGui(ImGuiConfigFlags imGuiConfigFlags);
	void SetDarkTheme();
	void SetupImGuiFont(const char* filename, float size_pixels, const ImFontConfig* font_cfg_template = NULL, const char* boldFontFile = nullptr);

	void ShowGUIMenuBar();
	void ShowGUIStats();

	double lastXMousePos = 0, lastYMousePos = 0;
};