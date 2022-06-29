#pragma once
#include "Scene.h"
#include "Mesh.h"

void Scene::Start() {
	Mesh coneMesh = Mesh::Cone(30, 20, 20);
	testMesh = new Mesh(coneMesh);

    modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -600.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(10.f));
    VPMatrix = glm::perspective<float>(glm::radians(90.f), 800 / 600.f, 0.1f, 1000.f) * glm::lookAt(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f) + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
    mvpMatrix = VPMatrix * modelMatrix;
}

void Scene::Update() {

}