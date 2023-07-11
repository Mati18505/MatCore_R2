#include "OpenGL/MeshBuffer.h"
#include <glad/glad.h>

namespace MatCore
{
	MeshBuffer::MeshBuffer()
	{
		//create VAO
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		//bind
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

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

	MeshBuffer::~MeshBuffer()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
	}
	void MeshBuffer::Bind() const
	{
		glBindVertexArray(VAO);
	}
	void MeshBuffer::Update(Mesh& mesh) //TODO std::vector<T>, std::vector<index>
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Mesh::Vertex) * mesh.GetVertices()->size(), mesh.GetVertices()->data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.GetTriangles()->size(), mesh.GetTriangles()->data(), GL_STATIC_DRAW);
	}
}