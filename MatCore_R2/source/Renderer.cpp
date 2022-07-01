#pragma once
#include "Renderer.h"
#include <glad.h>
#include "Mesh.h"
#include "Transform.h"
#include "Material.h"
#include "Camera.h"
#include "Scene.h"
#include "Application.h"

Renderer::Renderer() {
    auto view = applicationP->scene->entitiesRegistry.view<Mesh>();
    for (auto entity : view)
    {
        Mesh& mesh = view.get<Mesh>(entity);
        MeshRenderer::Init(mesh);
    }
}

Renderer::~Renderer()
{
    auto view = applicationP->scene->entitiesRegistry.view<Mesh>();
    for (auto entity : view)
    {
        Mesh& mesh = view.get<Mesh>(entity);
        MeshRenderer::DeInit(mesh);
    }
}

void Renderer::RenderScene(){
	glClearColor(0.2f, 0.7f, 1.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 800, 600);

    auto group = applicationP->scene->entitiesRegistry.group<Mesh>(entt::get<Transform, Material>);
    for (auto entity : group)
    {
        Mesh& mesh = group.get<Mesh>(entity);
        Transform& transform = group.get<Transform>(entity);
        Material& material = group.get<Material>(entity);
        MeshRenderer::RenderMesh(mesh, transform, material);
    }
}


void MeshRenderer::Init(Mesh& mesh) {
    //create VAO
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);
    glGenVertexArrays(1, &mesh.VAO);

    //bind
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);

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

void MeshRenderer::RenderMesh(Mesh& mesh, Transform& transform, Material& material) {
    //if (mesh == nullptr) /*error*/ return;

    // UpdateVBO
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Mesh::Vertex) * mesh.GetVertices()->size(), mesh.GetVertices()->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.GetTriangles()->size(), mesh.GetTriangles()->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Set MVP Uniform 
    material.SetMVPMatrix(transform.GetModelMatrix(), applicationP->scene->camera->GetVPMatrix());
    material.SetSelfUniforms();

    //Draw VAO
    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)mesh.GetTriangles()->size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void MeshRenderer::DeInit(Mesh& mesh) {
    glDeleteBuffers(1, &mesh.VBO);
    glDeleteBuffers(1, &mesh.EBO);
    glDeleteVertexArrays(1, &mesh.VAO);
}