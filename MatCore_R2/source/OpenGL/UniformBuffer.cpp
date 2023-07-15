#include "OpenGL/UniformBuffer.h"
#include <glad/glad.h>

namespace MatCore
{
	UniformBuffer::UniformBuffer(size_t byteSize)
		: GPUResource()
	{
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, byteSize, nullptr, GL_STATIC_DRAW); //dynamic?
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	UniformBuffer::UniformBuffer(size_t byteSize, const void* data)
		: GPUResource()
	{
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, byteSize, data, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &ubo);
	}

	void UniformBuffer::Bind(unsigned int slot) const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::UpdatePtr(size_t byteSize, const void* data)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, byteSize, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}