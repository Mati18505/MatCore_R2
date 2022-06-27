#pragma once
#include "Renderer.h"
#include <glad.h>
#include "MeshRenderer.h"
#include "Mesh.h"

Renderer::Renderer() {
	
}

void Renderer::RenderScene(){
	glClearColor(0.2f, 0.7f, 1.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderMesh(testMeshRenderer);
}

void RenderMesh(MeshRenderer* meshRenderer) {
    //create VAO
    unsigned int VAO, VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //pos
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
    glBindBuffer, GL_ARRAY_BUFFER(0);
    glBindBuffer, GL_ELEMENT_ARRAY_BUFFER(0);
    glBindVertexArray(0);
}