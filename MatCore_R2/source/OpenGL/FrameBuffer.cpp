#include "OpenGL/FrameBuffer.h"
#include <glad/glad.h>
#include <Log.h>

namespace MatCore
{
	FrameBuffer::FrameBuffer(int width, int height)
        : GPUResource()
	{
        glCreateFramebuffers(1, &frameBuffer);

        TextureDescription desc;
        desc.minFilter = TextureDescription::Filter::Linear;
        desc.magFilter = TextureDescription::Filter::Linear;
        desc.wrapMode = TextureDescription::WrapMode::Clamp;
        desc.internalFormat = TextureDescription::Format::RGB8;
        desc.mipmapsCount = 1;
        desc.width = width;
        desc.height = height;
        colorTexture = Resource<Texture2D>(std::make_shared<Texture2D>(desc));

        glNamedFramebufferTexture(frameBuffer, GL_COLOR_ATTACHMENT0, (GLuint)(GLuint*)colorTexture.GetBuffer()->GetRawHandle(), 0);

        glCreateRenderbuffers(1, &RBO);
        glNamedRenderbufferStorage(RBO, GL_DEPTH_COMPONENT24, width, height);
        glNamedFramebufferRenderbuffer(frameBuffer, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

        auto fboStatus = glCheckNamedFramebufferStatus(frameBuffer, GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
            LOG_CORE_ERROR("Framebuffer error: Framebuffer is not complete: {0}", fboStatus);
	}
	FrameBuffer::~FrameBuffer()
	{
        glDeleteRenderbuffers(1, &RBO);
        glDeleteFramebuffers(1, &frameBuffer);
	}
	void FrameBuffer::Bind() const
	{
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	}
    void FrameBuffer::BindTexture(unsigned int slot) const
    {
        colorTexture.GetBuffer()->Bind(slot);
    }
    const Resource<Texture2D>& FrameBuffer::GetTexture() const {
        return colorTexture;
    }
    Resource<Texture2D> FrameBuffer::GetTexture() {
        return colorTexture;
    }
}
