#include "MatCore.h"

using namespace MatCore;
class SandboxScene : public Scene{
public:
    SandboxScene() : entity(CreateEntity()), Scene() { LOG_INFO("SandboxScene constructed!"); }
    ~SandboxScene();
	void Start() override;
	void Update() override;
    void Render()  override {}
private:
    Entity entity;
	double lastXMousePos{ 0 }, lastYMousePos{ 0 };
};

Scene* Application::ApplicationStart(){
	LOG_INFO("Sandbox start");
	return new SandboxScene();
}

void SandboxScene::Start() {
    LOG_INFO("SandboxScene Start!");
    Mesh coneMesh = Mesh::Cone(360, 7, 7);
    Mesh circleMesh = Mesh::Circle(360, 7);
    
    //entity 1
    entity.AddComponent<MeshComponent>(coneMesh);
    entity.GetComponent<Transform>().position = { 5.f, 0.f, -20.f };
    entity.AddComponent<Material>();

    Entity entity3 = CreateEntity();
    entity3.AddComponent<MeshComponent>(circleMesh);
    entity3.GetComponent<Transform>().position = { 17.f, 0.f, -20.f };
    entity3.AddComponent<Material>();

    Entity entity2 = CreateEntity();
    entity2.AddComponent<MeshComponent>(coneMesh);
    entity2.GetComponent<Transform>().position = { -5.f, 0.f, -20.f };
    entity2.AddComponent<Material>();

    //testy
    {
        Entity e3 = CreateEntity();
        e3.AddComponent<Material>();
        DestroyEntity(e3);
        LOG_WARN(e3.HasComponent<Material>());
        e3.RemoveComponent<Material>();
    }

    //Camera
    camera = new Camera(90, Camera::CameraType::perspective);
    camera->SetYaw(-90);
    camera->SetCameraClip(1.f, 10000.f);

    //£adowanie modeli
    Model models[5]{ 
        {"Assets/test/Models/models/cyberpunkCar/untitled.obj", this},
        {"Assets/test/Models/models/Backpack/survivalBackpack/backpack.obj", this},
        {"Assets/test/Models/models/nanosuit/nanosuit.fbx", this },
        {"Assets/test/Models/models/spider/spider.obj", this},
        {"Assets/test/Models/models/cat/cat.fbx", this} 
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
    entity.GetComponent<Transform>().rotation.x++;

    glm::vec3 cameraFront = glm::normalize(camera->GetCameraFront());
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, camera->GetCameraUp()));
    glm::vec3 cameraUp = glm::normalize(camera->GetCameraUp());

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

    camera->SetCameraPos(camera->GetCameraPos() + cameraTranslate);

    auto [x, y] = Input::GetMousePosition();
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

SandboxScene::~SandboxScene(){
    delete this->camera;
}