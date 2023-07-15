#pragma once
#include "Bindable.h"
#include "OpenGL/GPUResource.h"

namespace MatCore {
	struct TextureDescription
	{
		enum class Format
		{
			RGB8,
			RGBA8
		};
		enum class Filter
		{
			Linear,
			Nearest,
			MipLinear
		};
		enum class WrapMode
		{
			Repeat,
			Clamp
		};

		Format internalFormat = Format::RGBA8;
		uint32_t width;
		uint32_t height;
		Filter minFilter = Filter::MipLinear;
		Filter magFilter = Filter::Linear;
		WrapMode wrapMode = WrapMode::Repeat;
		uint32_t mipmapsCount = 4;
	};

	class Texture2D : public GPUResource {
	public:
		explicit Texture2D(TextureDescription description);
		~Texture2D() override;

		unsigned int GetWidth() const { return description.width; }
		unsigned int GetHeight() const { return description.height; }
		void Bind(unsigned int slot = 0) const;
		void* GetRawHandle() { return (void*)ID; }
		void SetData(TextureDescription::Format format, const uint8_t* data, bool generateMipmaps = true);
		const TextureDescription& GetDescription() { return description; }
	private:
		uint32_t ID;
		TextureDescription description;
	};

}