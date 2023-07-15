#include "pch.h"

#include "Factory.h"
#include <stb_image.h>

namespace MatCore
{
	Resource<Texture2D> MatCore::Factory::CreateTextureAssetFromFile(const std::string& path) const
	{
		TextureDescription desc;
		int width, height, imageChannels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &imageChannels, 0);
		if (!data)
		{
			LOG_CORE_ERROR("Failed to load image! path: {0}", path);
			assert(false);
		}
		desc.width = width;
		desc.height = height;

		TextureDescription::Format imageFormat;
		switch (imageChannels)
		{
		case 3: imageFormat = TextureDescription::Format::RGB8;
			break;
		case 4: imageFormat = TextureDescription::Format::RGBA8;
			break;
		default:
			LOG_CORE_WARN("Image format not supported! channels: {0}", imageChannels);
			assert(false);
			break;
		}
		desc.internalFormat = imageFormat;

		auto texture = Resource<Texture2D>(std::make_shared<Texture2D>(desc));
		texture.GetBuffer()->SetData(imageFormat, data);
		stbi_image_free(data);
		return texture;
	}
}