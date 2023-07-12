#include "pch.h"

#include "Renderer.h"
#include <glad/glad.h>
#include "MeshComponent.h"
#include "Mesh.h"
#include "Transform.h"
#include "Material.h"
#include "Cameras/Camera.h"
#include "Scene.h"
#include "Application.h"
#include "Log.h"

MatCore::Renderer::Renderer() {

}

MatCore::Renderer::~Renderer(){

}

void MatCore::Renderer::RenderScene(){
    glClearColor(0.2f, 0.7f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, applicationP->windowWidth, applicationP->windowHeight);

    auto mainCameraOpt = applicationP->scene->GetMainCamera();
    if (!mainCameraOpt.has_value())
        return;
    Camera mainCamera = mainCameraOpt.value();

    vertices = triangles = drawCalls = 0;
    auto group = applicationP->scene->entitiesRegistry.group<>(entt::get<MeshComponent, Transform, Material>);
    for (auto entity : group)
    {
        MeshComponent& meshComponent = group.get<MeshComponent>(entity);
        Transform& transform = group.get<Transform>(entity);
        Material& material = group.get<Material>(entity);
        MeshRenderer::RenderMesh(meshComponent, transform, material, mainCamera);
        vertices += meshComponent.mesh.GetVertices()->size();
        triangles += meshComponent.mesh.GetTriangles()->size();
        drawCalls++;
    }
}


void MatCore::MeshRenderer::OnConstruct(entt::registry&, entt::entity entity){
    MeshComponent& meshComponent = applicationP->scene->entitiesRegistry.get<MeshComponent>(entity);
    Init(meshComponent);
}

void MatCore::MeshRenderer::OnDestroy(entt::registry&, entt::entity entity){
    MeshComponent& meshComponent = applicationP->scene->entitiesRegistry.get<MeshComponent>(entity);
    DeInit(meshComponent);
}

void MatCore::MeshRenderer::Init(MeshComponent& meshComponent) {
    //create VAO
    glGenBuffers(1, &meshComponent.VBO);
    glGenBuffers(1, &meshComponent.EBO);
    glGenVertexArrays(1, &meshComponent.VAO);

    //bind
    glBindVertexArray(meshComponent.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, meshComponent.VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshComponent.EBO);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    //uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(offsetof(Mesh::Vertex, Mesh::Vertex::uv)));
    glEnableVertexAttribArray(1);

    //color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(offsetof(Mesh::Vertex, Mesh::Vertex::color)));
    glEnableVertexAttribArray(2);

    //normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(offsetof(Mesh::Vertex, Mesh::Vertex::normal)));
    glEnableVertexAttribArray(3);

    //Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MatCore::MeshRenderer::RenderMesh(MeshComponent& meshComponent, Transform& transform, Material& material, Camera& camera) {
    if (meshComponent.VAO == NULL) { LOG_CORE_WARN("MeshComponent VAO is NULL!"); return; }

    // UpdateVBO
    glBindBuffer(GL_ARRAY_BUFFER, meshComponent.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Mesh::Vertex) * meshComponent.mesh.GetVertices()->size(), meshComponent.mesh.GetVertices()->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshComponent.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * meshComponent.mesh.GetTriangles()->size(), meshComponent.mesh.GetTriangles()->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    material.SetUniforms();
    material.SetMVPMatrix(transform.GetGlobalModelMatrix(), camera.GetProjection() * camera.GetView());
    material.SetSelfUniforms();

    //Draw VAO
    glBindVertexArray(meshComponent.VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)meshComponent.mesh.GetTriangles()->size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void MatCore::MeshRenderer::DeInit(MeshComponent& meshComponent) {
    glDeleteBuffers(1, &meshComponent.VBO);
    glDeleteBuffers(1, &meshComponent.EBO);
    glDeleteVertexArrays(1, &meshComponent.VAO);
}