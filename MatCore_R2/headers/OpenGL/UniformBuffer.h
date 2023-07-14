#pragma once
#include "Bindable.h"
#include "GPUResource.h"
#include <cstdint>

namespace MatCore
{
	class UniformBuffer : public GPUResource
	{
	public:
		explicit UniformBuffer(size_t byteSize);
		UniformBuffer(size_t byteSize, const void* data);

		~UniformBuffer() override;
		UniformBuffer(const UniformBuffer&) = delete;
		UniformBuffer& operator= (const UniformBuffer&) = delete;
		UniformBuffer(UniformBuffer&&) = delete;
		UniformBuffer& operator= (UniformBuffer&&) = delete;

		void Bind(unsigned int slot = 0) const;

		void UpdatePtr(size_t byteSize, const void* data);
		
	private:
		uint32_t ubo;
	};

	template<typename T>
	class UniformBufferT : public UniformBuffer {
	public:
		explicit UniformBufferT()
			: UniformBuffer(sizeof(T))
		{}

		explicit UniformBufferT(const T& bufferContent)
			: UniformBuffer(sizeof(T), (const void*)&bufferContent)
		{}

		void Update(const T& bufferContent)
		{
			UpdatePtr(sizeof(T), (const void*)&bufferContent);
		}
	};
}