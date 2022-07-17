#include "Editor.h"
#include "Dependece/ImGUI/imgui.h"
#include "Dependece/ImGUI/imgui_impl_glfw.h"
#include "Dependece/ImGUI/imgui_impl_opengl3.h"
#include "Utils.h"

using namespace MatCore;

Scene* Application::ApplicationStart() {
	return new EditorScene();
}

EditorScene::EditorScene()
	:Scene()
{
	ImGuiConfigFlags imGuiConfig = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiDockNodeFlags_PassthruCentralNode;
	SetupImGui(imGuiConfig);
	ImFontConfig fontConfig = ImFontConfig();
	SetupImGuiFont("Assets/calibri.ttf", 20, &fontConfig);
	
	camera = new Camera(90, Camera::CameraType::perspective);
	camera->SetYaw(-90);
	camera->SetCameraClip(0.01f, 1000.f);
}

EditorScene::~EditorScene()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	delete this->camera;
}

void EditorScene::Start()
{
	Mesh coneMesh = Mesh::Cone(360, 10, 5);
	for (size_t i = 0; i < 50; i++)
	{
		Entity t = CreateEntity();
		t.AddComponent<MeshComponent>(coneMesh);
		t.AddComponent<Material>();
	}

	Model model("Assets/test/Models/models/nanosuit/nanosuit.fbx");
	Mesh modelM;
	std::vector meshes = model.GetMeshes();
	modelM.CombineMeshes(&meshes[0], meshes.size());

	Entity modelEntity = CreateEntity("Nanosuit Model");
	modelEntity.AddComponent<MeshComponent>(modelM);
	modelEntity.AddComponent<Material>();
	if (!model.GetTextures().empty())
		modelEntity.GetComponent<Material>().albedo = model.GetTextures()[0];
	modelEntity.GetComponent<Transform>().position.z = 10;

	Entity child = CreateEntity("Child", modelEntity);
	Entity child2 = CreateEntity("Child2", child);
}

void EditorScene::Update()
{
	if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard || Input::IsKeyPressed(MC_KEY_F1))
	{
		auto [x, y] = Input::GetMousePosition();
		lastXMousePos = x;
		lastYMousePos = -y;
		return;
	}
		
	//TODO: zamieniæ zarz¹dzanie kamer¹ na skrypt
	glm::vec3 cameraFront = glm::normalize(camera->GetCameraFront());
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, camera->GetCameraUp()));
	glm::vec3 cameraUp = glm::normalize(camera->GetCameraUp());

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

	camera->SetCameraPos(camera->GetCameraPos() + cameraTranslate);

	auto[x, y] = Input::GetMousePosition();
	double xOffset = x - lastXMousePos;
	double yOffset = -y - lastYMousePos;

	lastXMousePos = x;
	lastYMousePos = -y;

	float sensitivity = 0.2f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	camera->SetYaw(camera->GetYaw() + (float)xOffset);
	camera->SetPitch(camera->GetPitch() + (float)yOffset);

	if (camera->GetPitch() > 89.0f)
		camera->SetPitch(89.0f);
	if (camera->GetPitch() < -89.0f)
		camera->SetPitch(-89.0f);
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
	ImGui::ShowDemoWindow();

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

void EditorScene::SetupImGuiFont(const char* filename, float size_pixels, const ImFontConfig* fontConfigFlags)
{
	ImGuiIO& io = ImGui::GetIO();
	ImVector<ImWchar> ranges;
	ImFontGlyphRangesBuilder builder;
	builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
	builder.AddText(u8"¹æê³ñóœŸ¿¥ÆÊ£ÑÓŒ¯");
	builder.BuildRanges(&ranges);
	io.Fonts->AddFontFromFileTTF(filename, size_pixels, fontConfigFlags, ranges.Data);
	io.Fonts[0].Build();
}

void EditorScene::ShowGUIMenuBar() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu(u8"Narzêdzia"))
		{
			char buf[200]{};
			if (ImGui::InputTextWithHint("Model", u8"Scie¿ka do pliku", buf, sizeof(buf), ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue)) {
				if (EditorUtils::LoadModel(this, buf))
					LOG_INFO("Model \"{0}\" successfully loaded!", buf);
				else
					LOG_WARN("Cannot load model \"{0}\"", buf);
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
	ImGui::SetNextWindowBgAlpha(0.35f);
	if (ImGui::Begin("Statystyki", NULL, window_flags))
	{
		ImGui::Text("Statystyki renderowania");
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (timer < 100.f)
			timer += applicationP->deltaTime;
		else
		{
			timer = 0;
			FPS = 1000.f / applicationP->deltaTime;
		}
		ImGui::Text("FPS: %.1f", FPS);
		
	}
	ImGui::End();
}