#include "OpenGL/OpenGLRenderAPI.h"
#include <glad/glad.h>

namespace MatCore
{
	void OpenGLRenderAPI::DrawTriangles(int count) const
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}
	void OpenGLRenderAPI::DrawIndexed(int count) const
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}

	void OpenGLRenderAPI::ClearColorAndDepth() const
	{
		glClearColor(0.2f, 0.7f, 1.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::InitOpenGL(int windowWidth, int windowHeight) const
	{
		gladLoadGL();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		SetViewportSize(windowWidth, windowHeight);
	}

	void OpenGLRenderAPI::SetViewportSize(int startX, int startY, int windowWidth, int windowHeight) const
	{
		glViewport(startX, startY, windowWidth, windowHeight);
	}

	void OpenGLRenderAPI::BindScreenFrameBuffer() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLRenderAPI::Enable(Option opt) const
	{
		switch (opt)
		{
		case Option::DEPTH_TEST:
			glEnable(GL_DEPTH_TEST);
		}
	}

	void OpenGLRenderAPI::Disable(Option opt) const
	{
		switch (opt)
		{
		case Option::DEPTH_TEST:
			glDisable(GL_DEPTH_TEST);
		}
	}

}
