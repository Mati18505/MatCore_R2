#pragma once
#include "Scene.h"

#include "MeshComponent.h"
#include "Transform.h"
#include "material.h"
#include "Camera.h"

void Scene::Start() {
    Mesh coneMesh = Mesh::Cone(30, 20, 20);
    Mesh circleMesh = Mesh::Circle(30, 20);

    //entity 1
    entity = entitiesRegistry.create();
    entitiesRegistry.emplace<MeshComponent>(entity, coneMesh);

    Transform& transform = entitiesRegistry.emplace<Transform>(entity);
    transform.position = glm::vec3(150.f, 0.f, -600.f);
    transform.scale = glm::vec3(10.f, 10.f, 10.f);

    entitiesRegistry.emplace<Material>(entity, "./Shaders/color.vs", "./Shaders/color.fs");

    auto entity3 = entitiesRegistry.create();
    entitiesRegistry.emplace<MeshComponent>(entity3, circleMesh);
    Transform& transform3 = entitiesRegistry.emplace<Transform>(entity3);
    transform3.position = glm::vec3(500.f, 0.f, -600.f);
    transform3.rotation = glm::vec3(0.f, 180.f, 90.f);
    transform3.scale = glm::vec3(10.f, 10.f, 10.f);
    entitiesRegistry.emplace<Material>(entity3, "./Shaders/color.vs", "./Shaders/color.fs");

    //entity 2
    entt::entity entity2 = entitiesRegistry.create();
    entitiesRegistry.emplace<MeshComponent>(entity2, coneMesh);

    Transform& transform2 = entitiesRegistry.emplace<Transform>(entity2);
    transform2.position = glm::vec3(-150.f, 0.f, -600.f);
    transform2.scale = glm::vec3(10.f, 10.f, 10.f);

    entitiesRegistry.emplace<Material>(entity2, "./Shaders/color.vs", "./Shaders/color.fs");

    //Camera
    camera = new Camera(90, Camera::CameraType::orthographic);
    camera->SetYaw(-90);
}

void Scene::Update() {
    Transform& transform = entitiesRegistry.get<Transform>(entity);
    transform.rotation.x++;
}

Scene::~Scene() {
    delete this->camera;
}