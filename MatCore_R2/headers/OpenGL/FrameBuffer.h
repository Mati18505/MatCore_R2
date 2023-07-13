#pragma once
#include "Bindable.h"
#include "GPUResource.h"
#include <cstdint>

namespace MatCore {
	class FrameBuffer : public Bindable, public GPUResource
	{
	public:
		explicit FrameBuffer(int width, int height);
		~FrameBuffer() override;
		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer& operator= (const FrameBuffer&) = delete;
		FrameBuffer(FrameBuffer&&) = delete;
		FrameBuffer& operator= (FrameBuffer&&) = delete;

		void Bind() const;
		void BindTexture() const;
	private:
		uint32_t frameBuffer;
		uint32_t textureColorBuffer;
		uint32_t RBO;
	};
}
