#include "OpenGL/TextureBuffer.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <Log.h>

namespace MatCore
{
	Texture2D::Texture2D(const std::string& path)
	{
		int imageWidth, imageHeight, imageChannels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &imageWidth, &imageHeight, &imageChannels, 0);
		if (!data) {
			LOG_CORE_ERROR("Failed to load image! path: {0}", path);
			return;
		}
		width = imageWidth;
		height = imageHeight;

		glCreateTextures(GL_TEXTURE_2D, 1, &ID);
		glTextureStorage2D(ID, 4, GL_RGBA8, imageWidth, imageHeight);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLenum format = GL_RGB;
		switch (imageChannels)
		{
		case 3: format = GL_RGB;
			break;
		case 4: format = GL_RGBA;
			break;
		default: LOG_CORE_WARN("Image format not supported! channels: {0}", imageChannels);
			break;
		}

		glTextureSubImage2D(ID, 0, 0, 0, imageWidth, imageHeight, format, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(ID); //TODO: zamieniæ na anisotropic filtering - wymaga rozszerzenia GL
		stbi_image_free(data);
	}
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &ID);
	}
	void Texture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, ID);
	}
}