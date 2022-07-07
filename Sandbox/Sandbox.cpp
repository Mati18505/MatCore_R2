#include "Application.h"
#include "Log.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "Transform.h"
#include "material.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "Log.h"

class SandboxScene : public Scene{
public:
    SandboxScene() : entity(entt::null), Scene() { LOG_INFO("SandboxScene constructed!"); }
    ~SandboxScene();
	void Start();
	void Update();
private:
	entt::entity entity;
    entt::entity e;
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
    entity = entitiesRegistry.create();
    entitiesRegistry.emplace<MeshComponent>(entity, coneMesh);

    Transform& transform = entitiesRegistry.emplace<Transform>(entity);
    transform.position = glm::vec3(5.f, 0.f, -20.f);
    transform.scale = glm::vec3(1.f, 1.f, 1.f);

    entitiesRegistry.emplace<Material>(entity, "./Shaders/color.vs", "./Shaders/color.fs");


    auto entity3 = entitiesRegistry.create();
    entitiesRegistry.emplace<MeshComponent>(entity3, circleMesh);

    Transform& transform3 = entitiesRegistry.emplace<Transform>(entity3);
    transform3.position = glm::vec3(17.f, 0.f, -20.f);
    transform3.rotation = glm::vec3(0.f, 180.f, 90.f);
    transform3.scale = glm::vec3(1.f, 1.f, 1.f);

    entitiesRegistry.emplace<Material>(entity3, "./Shaders/color.vs", "./Shaders/color.fs");

    //entity 2
    entt::entity entity2 = entitiesRegistry.create();
    entitiesRegistry.emplace<MeshComponent>(entity2, coneMesh);


    Transform& transform2 = entitiesRegistry.emplace<Transform>(entity2);
    transform2.position = glm::vec3(-5.f, 0.f, -20.f);
    transform2.scale = glm::vec3(1.f, 1.f, 1.f);

    entitiesRegistry.emplace<Material>(entity2, "./Shaders/color.vs", "./Shaders/color.fs");

    //Camera
    camera = new Camera(90, Camera::CameraType::perspective);
    camera->SetYaw(-90);
    camera->SetCameraClip(1.f, 10000.f);

    e = entitiesRegistry.create();
    entitiesRegistry.emplace<MeshComponent>(e, coneMesh);
    entitiesRegistry.emplace<Material>(e, "./Shaders/color.vs", "./Shaders/color.fs");
    entitiesRegistry.emplace<Transform>(e);
}

void SandboxScene::Update() {
    Transform& transform = entitiesRegistry.get<Transform>(entity);
    transform.rotation.x++;

    glm::vec3 cameraFront = glm::normalize(camera->GetCameraFront());
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, camera->GetCameraUp()));

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
        cameraTranslate.y--;
    }
    if (glfwGetKey(applicationP->window, GLFW_KEY_E) == GLFW_PRESS) {
        cameraTranslate.y++;
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

    camera->SetYaw(camera->GetYaw() + xOffset);
    camera->SetPitch(camera->GetPitch() + yOffset);

    if (camera->GetPitch() > 89.0f)
        camera->SetPitch(89.0f);
    if (camera->GetPitch() < -89.0f)
        camera->SetPitch(-89.0f);
}

SandboxScene::~SandboxScene(){
    delete this->camera;
}