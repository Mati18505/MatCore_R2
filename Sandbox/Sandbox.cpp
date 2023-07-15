#include "MatCore.h"
#include <glm/glm.hpp>

using namespace MatCore;
class SandboxScene : public Scene{
public:
    SandboxScene() : Scene() { LOG_INFO("SandboxScene constructed!"); }
    void OnEvent(Event& e) override;
	void Start() override;
	void Update() override;
    void Render()  override {}
private:
    Entity cameraEntity;
	double lastXMousePos{ 0 }, lastYMousePos{ 0 };
};

Scene* Application::ApplicationStart(){
	LOG_INFO("Sandbox start");
	return new SandboxScene();
}

void SandboxScene::Start() {
    LOG_INFO("SandboxScene Start!");
    
    Resource<Shader> vertex = Factory::Get().CreateShaderAssetFromFile("Resources/Shaders/default.vs", Shader::ShaderType::vertex);
    Resource<Shader> fragment = Factory::Get().CreateShaderAssetFromFile("Resources/Shaders/default.fs", Shader::ShaderType::fragment);
    Resource<ShaderProgram> shader = Factory::Get().CreateShaderProgramAssetFromShaders(vertex, fragment);
    shaderLibrary.Add("default", shader);
    
    Mesh coneMesh = Mesh::Cone(360, 7, 7);
    Mesh circleMesh = Mesh::Circle(360, 7);
    
    Material material{ shaderLibrary.Get("default") };

    Entity entity3 = CreateEntity();
    entity3.AddComponent<MeshComponent>(circleMesh);
    entity3.GetComponent<Transform>().position = { 17.f, 0.f, -20.f };
    entity3.AddComponent<Material>(material);

    Entity entity2 = CreateEntity();
    entity2.AddComponent<MeshComponent>(coneMesh);
    entity2.GetComponent<Transform>().position = { -5.f, 0.f, -20.f };
    entity2.AddComponent<Material>(material);

    //testy
    {
        Entity e3 = CreateEntity();
        e3.AddComponent<Material>(material);
        DestroyEntity(e3);
        LOG_WARN(e3.HasComponent<Material>());
        e3.RemoveComponent<Material>();
    }
    //Camera
    cameraEntity = CreateEntity();
    cameraEntity.GetComponent<Transform>().position = { 147.f, 172.f, 142.f };
    cameraEntity.GetComponent<Transform>().rotation = { -32.f, -70.f, 0.f };
    auto& camera = cameraEntity.AddComponent<CameraComponent>().camera;
    camera.cameraType = SceneCamera::CameraType::perspective; 
    cameraEntity.GetComponent<CameraComponent>().primary = true;

    //£adowanie modeli
    Model models[5]{ 
        {"Assets/test/Models/models/cyberpunkCar/untitled.obj", this, "default"},
        {"Assets/test/Models/models/Backpack/survivalBackpack/backpack.obj", this, "default"},
        {"Assets/test/Models/models/nanosuit/nanosuit.fbx", this, "default" },
        {"Assets/test/Models/models/spider/spider.obj", this, "default"},
        {"Assets/test/Models/models/cat/cat.fbx", this, "default"}
    };
    int modelSizes[5]{ 10, 20, 10, 1, 10 };
    
    int j = 0;
    for (auto model : models) { 
        Entity e2 = model;
        Transform& modelTransform = e2.GetComponent<Transform>();
        modelTransform.position.x = j * 100;
        modelTransform.scale *= modelSizes[j];
        j++;
    }
}

void SandboxScene::Update() {
    OnRuntimeUpdate();

    auto& transform = cameraEntity.GetComponent<Transform>();
    glm::vec3 cameraFront = transform.GetLocalForwardVector();
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, { 0,1,0 }));
    glm::vec3 cameraUp = { 0,1,0 };

    glm::vec3 cameraTranslate{ 0,0,0 };
    int cameraSpeed = 2;

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
    cameraTranslate *= cameraSpeed;
    transform.position = transform.position + cameraTranslate;

    auto [x, y] = Input::GetMousePosition();
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

void SandboxScene::OnEvent(Event& e)
{
    
}