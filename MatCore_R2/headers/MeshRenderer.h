#pragma once

class Mesh;
struct MeshRenderer {
	Mesh* mesh;
	unsigned int VBO, VAO, EBO;
	bool isVAOCreated;
};