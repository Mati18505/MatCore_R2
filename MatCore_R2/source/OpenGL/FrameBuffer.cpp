#include "OpenGL/FrameBuffer.h"
#include <glad/glad.h>
#include <Log.h>

namespace MatCore
{
	FrameBuffer::FrameBuffer(int width, int height)
	{
        glCreateFramebuffers(1, &frameBuffer);
        
        glCreateTextures(GL_TEXTURE_2D, 1, &textureColorBuffer);
        glTextureParameteri(textureColorBuffer, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(textureColorBuffer, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(textureColorBuffer, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(textureColorBuffer, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTextureStorage2D(textureColorBuffer, 1, GL_RGB8, width, height);
        glNamedFramebufferTexture(frameBuffer, GL_COLOR_ATTACHMENT0, textureColorBuffer, 0);

        glCreateRenderbuffers(1, &RBO);
        glNamedRenderbufferStorage(RBO, GL_DEPTH_COMPONENT24, width, height);
        glNamedFramebufferRenderbuffer(frameBuffer, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

        auto fboStatus = glCheckNamedFramebufferStatus(frameBuffer, GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
            LOG_CORE_ERROR("Framebuffer error: Framebuffer is not complete: {0}", fboStatus);
	}
	FrameBuffer::~FrameBuffer()
	{
        glDeleteTextures(1, &textureColorBuffer);
        glDeleteRenderbuffers(1, &RBO);
        glDeleteFramebuffers(1, &frameBuffer);
	}
	void FrameBuffer::Bind() const
	{
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	}
    void FrameBuffer::BindTexture() const
    {
        glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    }
}
