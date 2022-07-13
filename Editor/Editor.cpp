#include "Editor.h"
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "Dependece/ImGUI/imgui.h"
#include "Dependece/ImGUI/imgui_impl_glfw.h"
#include "Dependece/ImGUI/imgui_impl_opengl3.h"

using namespace MatCore;

Scene* Application::ApplicationStart() {
	return new EditorScene();
}

EditorScene::EditorScene()
{
	//Setup IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	io->ConfigViewportsNoAutoMerge = true;

	ImGui::StyleColorsDark();
	
	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	//backends
	ImGui_ImplGlfw_InitForOpenGL(applicationP->window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	if (!io->Fonts->AddFontFromFileTTF("Assets/calibri.ttf", 22)) {
		LOG_ERROR("Unable to load font: Assets/calibri.ttf");
	}
	//io->Fonts->AddFontDefault();
	//ImFontAtlas::Build();
	//Camera
	camera = new Camera(90, Camera::CameraType::perspective);
	camera->SetYaw(-90);
	camera->SetCameraClip(1.f, 10000.f);
}

EditorScene::~EditorScene()
{
	//Shutdown
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	delete this->camera;
}

void EditorScene::Start()
{
}

void EditorScene::Update()
{
}

void EditorScene::Render()
{
	//New Frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//content
	ImGui::ShowDemoWindow();
	ImGui::Begin("Okno testowe");
	ImGui::End();

	//Render
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//Update platform windows
	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}
