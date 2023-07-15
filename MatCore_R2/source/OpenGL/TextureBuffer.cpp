#include "OpenGL/TextureBuffer.h"
#include <glad/glad.h>
#include <Log.h>

namespace MatCore
{
	static GLint GetGLFilterFromFilter(TextureDescription::Filter filter)
	{
		GLint glFilter{};
		switch (filter)
		{
		case TextureDescription::Filter::Linear:
			glFilter = GL_LINEAR;
			break;
		case TextureDescription::Filter::Nearest:
			glFilter = GL_NEAREST;
			break;
		case TextureDescription::Filter::MipLinear:
			glFilter = GL_LINEAR_MIPMAP_LINEAR;
		}
		return glFilter;
	}

	static GLint GetGLWrapFromWrap(TextureDescription::WrapMode wrap)
	{
		GLint glWrap{};
		switch (wrap)
		{
		case TextureDescription::WrapMode::Clamp:
			glWrap = GL_CLAMP_TO_EDGE;
			break;
		case TextureDescription::WrapMode::Repeat:
			glWrap = GL_REPEAT;
			break;
		}
		return glWrap;
	}
	
	static GLint GetGLInternalFormatFromFormat(TextureDescription::Format format)
	{
		GLenum glFormat{};
		switch (format)
		{
		case TextureDescription::Format::RGB8:
			glFormat = GL_RGB8;
			break;
		case TextureDescription::Format::RGBA8:
			glFormat = GL_RGBA8;
			break;
		}
		return glFormat;
	}
	
	static GLint GetGLFormatFromFormat(TextureDescription::Format format)
	{
		GLenum glFormat{};
		switch (format)
		{
		case TextureDescription::Format::RGB8:
			glFormat = GL_RGB;
			break;
		case TextureDescription::Format::RGBA8:
			glFormat = GL_RGBA;
			break;
		}
		return glFormat;
	}

	Texture2D::Texture2D(TextureDescription desc)
		: GPUResource(), description(desc)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &ID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GetGLFilterFromFilter(desc.minFilter));
		glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GetGLFilterFromFilter(desc.magFilter));
		glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GetGLWrapFromWrap(desc.wrapMode));
		glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GetGLWrapFromWrap(desc.wrapMode));

		GLenum internalFormat = GetGLInternalFormatFromFormat(desc.internalFormat);
		glTextureStorage2D(ID, desc.mipmapsCount, internalFormat, desc.width, desc.height);
	}
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &ID);
	}
	void Texture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, ID);
	}
	void Texture2D::SetData(TextureDescription::Format format, const uint8_t* data, bool generateMipmaps)
	{
		glTextureSubImage2D(ID, 0, 0, 0, description.width, description.height, GetGLFormatFromFormat(format), GL_UNSIGNED_BYTE, (const void*)data);
		if(generateMipmaps)
			glGenerateTextureMipmap(ID);
	}
}