#pragma once
#include "Bindable.h"
#include "GPUResource.h"
#include "Resource.h"
#include "TextureBuffer.h"
#include <cstdint>

namespace MatCore {
	class FrameBuffer : public Bindable, public GPUResource
	{
	public:
		explicit FrameBuffer(int width, int height);
		~FrameBuffer() override;

		void Bind() const;
		void BindTexture(unsigned int slot = 0) const;
	private:
		uint32_t frameBuffer;
		Resource<Texture2D> colorTexture;
		uint32_t RBO;
	};
}
