#include "Application.h"
#include "Log.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "Transform.h"
#include "material.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "Entity.h"
#include "Log.h"
#include "Model.h"
#include "Texture.h"

using namespace MatCore;
class SandboxScene : public Scene{
public:
    SandboxScene() : entity(CreateEntity()), Scene() { LOG_INFO("SandboxScene constructed!"); }
    ~SandboxScene();
	void Start();
	void Update();
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
    Model models[5]{("Assets/test/Models/models/cyberpunkCar/untitled.obj"),
        ("Assets/test/Models/models/Backpack/survivalBackpack/backpack.obj"),
        ("Assets/test/Models/models/nanosuit/nanosuit.fbx"),
        ("Assets/test/Models/models/spider/spider.obj"),
        ("Assets/test/Models/models/cat/cat.fbx") };
    int modelSizes[5]{ 10, 20, 10, 1, 10 };

    int j = 0;
    for (auto model : models) {
        for (size_t i = 0; i < model.GetMeshes().size(); i++)
        {
            Entity e2 = CreateEntity();
            e2.AddComponent<MeshComponent>(model.GetMeshes()[i]);
            e2.AddComponent<Material>();
            if (!model.GetTextures().empty())
                e2.GetComponent<Material>().albedo = model.GetTextures()[i];
            Transform& modelTransform = e2.GetComponent<Transform>();
            modelTransform.position.x = j * 100;
            modelTransform.scale *= modelSizes[j];
        }
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

    if (glfwGetKey(applicationP->window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraTranslate += cameraFront;
    }
    if (glfwGetKey(applicationP->window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraTranslate -= cameraRight;
    }
    if (glfwGetKey(applicationP->window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraTranslate -= cameraFront;
    }
    if (glfwGetKey(applicationP->window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraTranslate += cameraRight;
    }
    if (glfwGetKey(applicationP->window, GLFW_KEY_Q) == GLFW_PRESS) {
        cameraTranslate -= cameraUp;
    }
    if (glfwGetKey(applicationP->window, GLFW_KEY_E) == GLFW_PRESS) {
        cameraTranslate += cameraUp;
    }
    if (glfwGetKey(applicationP->window, GLFW_KEY_X) == GLFW_PRESS) {
        cameraSpeed *= 10;
    }
    cameraTranslate *= cameraSpeed;

    camera->SetCameraPos(camera->GetCameraPos() + cameraTranslate);

    double xpos, ypos;
    glfwGetCursorPos(applicationP->window, &xpos, &ypos);
    double xOffset = xpos - lastXMousePos;
    double yOffset = -ypos - lastYMousePos;

    lastXMousePos = xpos;
    lastYMousePos = -ypos;

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