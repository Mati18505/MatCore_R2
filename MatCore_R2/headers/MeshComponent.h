#pragma once
#include "Mesh.h"

struct MeshComponent {
	MeshComponent(Mesh mesh) : isVAOCreated(false), VAO(0), VBO(0), EBO(0) {
		this->mesh = mesh;
	}
	MeshComponent(const MeshComponent& other);


	unsigned int VAO, VBO, EBO;
	bool isVAOCreated;
	Mesh mesh;
};