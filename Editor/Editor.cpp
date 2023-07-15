#include "Editor.h"
#include "Dependece/ImGUI/imgui.h"
#include "Dependece/ImGUI/imgui_impl_glfw.h"
#include "Dependece/ImGUI/imgui_impl_opengl3.h"
#include "Utils.h"
#include <sstream>

using namespace MatCore;

Scene* Application::ApplicationStart() {
	return new EditorScene();
}

EditorScene::EditorScene()
	:Scene()
{
	ImGuiConfigFlags imGuiConfig = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiDockNodeFlags_PassthruCentralNode;
	SetupImGui(imGuiConfig);
	SetDarkTheme();
	ImFontConfig fontConfig = ImFontConfig();
	SetupImGuiFont("Resources/Fonts/Rubik/static/Rubik-Regular.ttf", 20, &fontConfig, "Resources/Fonts/Rubik/static/Rubik-Bold.ttf");
	
	LOG_INFO("Editor: Loading shaders");
	Resource<Shader> vs = Factory::Get().CreateShaderAssetFromFile("Resources/Shaders/default.vs", Shader::ShaderType::vertex);
	Resource<Shader> fs = Factory::Get().CreateShaderAssetFromFile("Resources/Shaders/default.fs", Shader::ShaderType::fragment);
	Resource<ShaderProgram> shader = Factory::Get().CreateShaderProgramAssetFromShaders(vs, fs);
	shaderLibrary.Add("default", shader);
	
	/*
	camera = new Camera(90, Camera::CameraType::perspective);
	camera->SetYaw(-90);
	camera->SetCameraClip(0.01f, 1000.f);*/
}

EditorScene::~EditorScene()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//delete this->camera;
}

void EditorScene::Start()
{
	Mesh coneMesh = Mesh::Cone(360, 10, 5);
	for (size_t i = 0; i < 6; i++)
	{
		Entity t = CreateEntity();
		t.AddComponent<MeshComponent>(coneMesh);
		
		t.AddComponent<Material>(shaderLibrary.Get("default"));
		t.GetComponent<Transform>().position.z = -10;
	}
	
	Model model("Assets/test/Models/models/nanosuit/nanosuit.fbx", this, "default");
	Model darthVaderModel("Assets/test/Models/models/darth-vader-by-oscar-creativo/source/DARTH VADER BAJA.fbx", this, "default");
	
	Entity modelEntity = model;
	modelEntity.GetComponent<Transform>().position.z = 10;
	Entity darthVader = darthVaderModel;
	auto& dVT = darthVader.GetComponent<Transform>();
	dVT.scale = { 2,2,2 };

	Entity child = CreateEntity("Child", modelEntity);
	Entity child2 = CreateEntity("Child2", child);
	Entity camera = CreateEntity("Camera", CreateEntity("Camera parent"));
	camera.AddComponent<CameraComponent>();
	Entity camera2 = CreateEntity("Camera2");
	camera2.AddComponent<CameraComponent>().primary = false;
}

void EditorScene::Update()
{
	OnRuntimeUpdate();
	if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard || Input::IsKeyPressed(MC_KEY_1))
	{
		auto [x, y] = Input::GetMousePosition();
		lastXMousePos = x;
		lastYMousePos = -y;
		return;
	}
	//TODO: zamieniæ zarz¹dzanie kamer¹ na skrypt
	Entity cameraEntity = GetMainRuntimeCameraEntity();
	if (!cameraEntity) return;
	auto& transform = cameraEntity.GetComponent<Transform>();

	//pitch - x yaw - y
	glm::vec3 cameraFront = transform.GetLocalForwardVector();
	glm::vec3 cameraUp = { 0, 1, 0 };
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	

	glm::vec3 cameraTranslate{ 0,0,0 };
	float cameraSpeed = 2;

	if (Input::IsKeyPressed(MC_KEY_W)) {
		cameraTranslate += cameraFront;
	}
	if (Input::IsKeyPressed(MC_KEY_A)) {
		cameraTranslate -= cameraRight;
	}
	if (Input::IsKeyPressed(MC_KEY_S)) {
		cameraTranslate -= cameraFront;
	}
	if (Input::IsKeyPressed(MC_KEY_D)) {
		cameraTranslate += cameraRight;
	}
	if (Input::IsKeyPressed(MC_KEY_Q)) {
		cameraTranslate -= cameraUp;
	}
	if (Input::IsKeyPressed(MC_KEY_E)) {
		cameraTranslate += cameraUp;
	}
	if (Input::IsKeyPressed(MC_KEY_X)) {
		cameraSpeed *= 10;
	}
	if (Input::IsKeyPressed(MC_KEY_C)) {
		cameraSpeed *= 0.1f;
	}
	cameraTranslate *= cameraSpeed;

	transform.position = transform.position + cameraTranslate;

	auto[x, y] = Input::GetMousePosition();
	double xOffset = x - lastXMousePos;
	double yOffset = -y - lastYMousePos;

	lastXMousePos = x;
	lastYMousePos = -y;

	float sensitivity = 0.2f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	transform.rotation.y = transform.rotation.y + (float)xOffset;
	transform.rotation.x = transform.rotation.x + (float)yOffset;

	if (transform.rotation.x > 89.0f)
		transform.rotation.x = 89.0f;
	if (transform.rotation.x < -89.0f)
		transform.rotation.x = -89.0f;
}

void EditorScene::Render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//content
	ShowGUIMenuBar();
	ShowGUIStats();
	hierarchyPanel.Render(this);
	assetsPanel.Render();

	//Render
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorScene::SetupImGui(ImGuiConfigFlags imGuiConfigFlags)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = imGuiConfigFlags;
	io.ConfigViewportsNoAutoMerge = true;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(applicationP->window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void EditorScene::SetDarkTheme()
{
	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

	// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

	// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Resize Grib
	colors[ImGuiCol_ResizeGrip] = { 0.2f, 0.2f, 0.2f, 1.f };
	colors[ImGuiCol_ResizeGripHovered] = { 0.2f, 0.2f, 0.2f, 1.f };
	colors[ImGuiCol_ResizeGripActive] = { 0.1f, 0.1f, 0.1f, 1.f };
}

void EditorScene::SetupImGuiFont(const char* regularFontFile, float size_pixels, const ImFontConfig* fontConfigFlags, const char* boldFontFile)
{
	ImGuiIO& io = ImGui::GetIO();
	ImVector<ImWchar> ranges;
	ImFontGlyphRangesBuilder builder;
	builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
	builder.AddText(u8"¹æê³ñóœŸ¿¥ÆÊ£ÑÓŒ¯");
	builder.BuildRanges(&ranges);

	if (boldFontFile != nullptr) {
		io.Fonts->AddFontFromFileTTF(boldFontFile, size_pixels, fontConfigFlags, ranges.Data);
	}
	io.FontDefault = io.Fonts->AddFontFromFileTTF(regularFontFile, size_pixels, fontConfigFlags, ranges.Data);
	io.Fonts[0].Build();
}

void EditorScene::ShowGUIMenuBar() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu(u8"Narzêdzia"))
		{
			if (ImGui::MenuItem("Load model"))
			{
				Entity modelEntity = EditorUtils::LoadModel(this);
				if (modelEntity)
					LOG_INFO("Model \"{0}\" successfully loaded!", modelEntity.GetComponent<TagComponent>().tag);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void EditorScene::ShowGUIStats()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	ImGui::SetNextWindowBgAlpha(0.5f);
	ImGui::SetNextWindowSize({ 300, 200 });
	if (ImGui::Begin("Statystyki", NULL, window_flags))
	{
		static double frameTime = 0;
		static float FPS = 0;
		static float timer = 0;

		ImGui::Text("Statystyki");
		ImGui::Separator();
		if (timer < 200.f)
			timer += applicationP->deltaTime;
		else
		{
			timer = 0;
			FPS = 1000.f / applicationP->deltaTime;
			frameTime = applicationP->deltaTime;
		}
		std::stringstream fpsS;
		fpsS << frameTime << " ms/frame (" << (int)FPS << " fps) ";
		ImGui::Text(fpsS.str().c_str());
		/*
		std::stringstream rendererS;
		auto& renderer = applicationP->renderer;
		rendererS << "Vertices: " << renderer->Vertices() << "\nTriangles: " << renderer->Triangles() << "\nDraw calls: " << renderer->DrawCalls();
		ImGui::Text(rendererS.str().c_str());*/
		
		std::stringstream entityCountS;
		entityCountS << "Obiekty: " << entitiesRegistry.alive();
		ImGui::Text(entityCountS.str().c_str());
		
		std::stringstream hoveredEntityS;
		Entity hoveredEntity = hierarchyPanel.GetSelectedEntity();
		hoveredEntityS << "Trzymany obiekt: " << (hoveredEntity != Entity::Null() ? hoveredEntity.GetComponent<TagComponent>().tag : "<empty>");
		ImGui::Text(hoveredEntityS.str().c_str());

	}
	ImGui::End();
}