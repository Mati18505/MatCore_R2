#include "OpenGL/StaticRenderer.h"
#include <glad/glad.h>

namespace MatCore
{
	void StaticRenderer::DrawIndexed(int count) const
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}

	void StaticRenderer::ClearColorAndDepth() const
	{
		glClearColor(0.2f, 0.7f, 1.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void StaticRenderer::InitOpenGL(int windowWidth, int windowHeight) const
	{
		gladLoadGL();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		SetViewportSize(windowWidth, windowHeight);
	}

	void StaticRenderer::SetViewportSize(int startX, int startY, int windowWidth, int windowHeight) const
	{
		glViewport(startX, startY, windowWidth, windowHeight);
	}

}
