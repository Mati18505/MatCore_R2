#include "Texture.h"
#include <stb_image.h>
#include <glad.h>
#include "Log.h"

MatCore::Texture2D::Texture2D(const char* path) {
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
	if (!data) {
		LOG_CORE_ERROR("Failed to load image! path: {0}", path);
		return;
	}
	this->width = width;
	this->height = height;

	glCreateTextures(GL_TEXTURE_2D, 1, &renderID);
	glTextureStorage2D(renderID, 1, GL_RGB8, width, height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTextureParameteri(renderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(renderID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLenum format = GL_RGB;
	switch (channels)
	{
	case 3: format = GL_RGB; 
		break;
	case 4: format = GL_RGBA; 
		break;
	default: LOG_CORE_WARN("Image format not supported! channels: {0}", channels);
		break;
	}
	
	glTextureSubImage2D(renderID, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

MatCore::Texture2D::~Texture2D() {
	glDeleteTextures(1, &renderID);
}

void MatCore::Texture2D::Bind(unsigned int slot) const{
	glBindTextureUnit(slot, renderID);
}