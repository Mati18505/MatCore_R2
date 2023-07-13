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
		if (!layoutSet)
			throw std::exception("Layout of MeshBuffer is not set!");
		glBindVertexArray(VAO);
	}
	void MeshBuffer::Update(size_t verticesByteSize, const void* verticesData, size_t indicesByteSize, const void* indicesData)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, verticesByteSize, verticesData, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indicesData, GL_STATIC_DRAW);
	}

	void MeshBuffer::SetLayout(BufferLayout layout)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		const auto& elements = layout.GetElements();
		uint32_t offset = 0;
		for (size_t i = 0; i < elements.size(); i++)
		{
			const auto& el = elements.at(i);
			GLenum type = layout.GetGLType(el.type);

			glVertexAttribPointer(i, el.count, type, el.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)offset);
			offset += el.size * el.count;
			glEnableVertexAttribArray(i);
		}
		layoutSet = true;
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void BufferLayout::Push(BufferLayoutElement::Type type, uint32_t count, bool normalized)
	{
		BufferLayoutElement el{};
		el.type = type;
		el.count = count;
		el.normalized = normalized;
		el.size = GetSizeOfType(type);

		elements.push_back(el);

		stride += el.size * el.count;
	}
	uint32_t BufferLayout::GetSizeOfType(Type type) const
	{
		uint32_t size = 0;
		switch (type)
		{
		case Type::Float:
			size = sizeof(GLfloat);
			break;
		case Type::Unsigned_int:
			size = sizeof(GLuint);
			break;
		}
		return size;
	}

	const std::vector<BufferLayoutElement>& BufferLayout::GetElements() const
	{
		return elements;
	}

	GLenum BufferLayout::GetGLType(Type type) const
	{
		switch (type)
		{
		case Type::Float:
			return GL_FLOAT;
			break;
		case Type::Unsigned_int:
			return GL_UNSIGNED_INT;
			break;
		}
	}
}