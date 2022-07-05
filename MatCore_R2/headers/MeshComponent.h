#pragma once
#include "Mesh.h"

struct MeshComponent {
	MeshComponent(Mesh mesh) : isVAOCreated(false), VAO(0), VBO(0), EBO(0) {
		this->mesh = mesh;
	}
	MeshComponent(const MeshComponent& other) = delete;
	MeshComponent(MeshComponent&& other) noexcept = default;
	
	MeshComponent& operator=(const MeshComponent& other) = delete;
	
	MeshComponent& operator=(MeshComponent&& other) noexcept = default;


	unsigned int VAO, VBO, EBO;
	bool isVAOCreated;
	Mesh mesh;
};