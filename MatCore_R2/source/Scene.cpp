#pragma once
#include "Scene.h"

#include "Mesh.h"
#include "Transform.h"
#include "material.h"
#include "Camera.h"

void Scene::Start() {
    Mesh coneMesh = Mesh::Cone(30, 20, 20);

    //entity 1
    entity = entitiesRegistry.create();
    entitiesRegistry.emplace<Mesh>(entity, coneMesh);

    Transform& transform = entitiesRegistry.emplace<Transform>(entity);
    transform.position = glm::vec3(150.f, 0.f, -600.f);
    transform.scale = glm::vec3(10.f, 10.f, 10.f);

    entitiesRegistry.emplace<Material>(entity, "./Shaders/color.vs", "./Shaders/color.fs");

    //entity 2
    entt::entity entity2 = entitiesRegistry.create();
    entitiesRegistry.emplace<Mesh>(entity2, coneMesh);

    Transform& transform2 = entitiesRegistry.emplace<Transform>(entity2);
    transform2.position = glm::vec3(-150.f, 0.f, -600.f);
    transform2.scale = glm::vec3(10.f, 10.f, 10.f);

    entitiesRegistry.emplace<Material>(entity2, "./Shaders/color.vs", "./Shaders/color.fs");

    //Camera
    camera = new Camera(90, Camera::CameraType::perspective);
    camera->SetYaw(-90);
}

void Scene::Update() {
    Transform& transform = entitiesRegistry.get<Transform>(entity);
    transform.rotation.x++;
}