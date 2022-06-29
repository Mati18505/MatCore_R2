#pragma once
#include "Scene.h"

#include "Mesh.h"
#include "Transform.h"

void Scene::Start() {
    Mesh coneMesh = Mesh::Cone(30, 20, 20);

    //entity 1
    entt::entity entity = entitiesRegistry.create();
    entitiesRegistry.emplace<Mesh>(entity, coneMesh);

    Transform& transform = entitiesRegistry.emplace<Transform>(entity);
    transform.position = glm::vec3(150.f, 0.f, -600.f);
    transform.scale = glm::vec3(10.f, 10.f, 10.f);

    //entity 2
    entt::entity entity2 = entitiesRegistry.create();
    entitiesRegistry.emplace<Mesh>(entity2, coneMesh);

    Transform& transform2 = entitiesRegistry.emplace<Transform>(entity2);
    transform2.position = glm::vec3(-150.f, 0.f, -600.f);
    transform2.scale = glm::vec3(10.f, 10.f, 10.f);

    //Camera
    VPMatrix = glm::perspective<float>(glm::radians(90.f), 800 / 600.f, 0.1f, 100000.f) * glm::lookAt(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f) + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
}

void Scene::Update() {

}