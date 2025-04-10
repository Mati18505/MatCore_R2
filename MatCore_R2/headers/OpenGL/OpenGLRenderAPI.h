#pragma once
#include "Bindable.h"
#include "TextureBuffer.h"
#include "Resource.h"

namespace MatCore
{
	class OpenGLRenderAPI
	{
	public:
		static OpenGLRenderAPI& Get()
		{
			static OpenGLRenderAPI r;
			return r;
		}
		
		OpenGLRenderAPI(const OpenGLRenderAPI&) = delete;
		OpenGLRenderAPI& operator=(const OpenGLRenderAPI& other) = delete;

		void Bind(const Bindable* bindable) const
		{
			bindable->Bind();
		}

		template<typename T>
		void Bind(Resource<T> bindable) const
		{
			Bindable* b = static_cast<Bindable*>(bindable.GetBuffer().get());
			Bind(b);
		}

		void BindTexture(const Resource<Texture2D> texture, int slot) const
		{
			texture.GetBuffer()->Bind(slot);
		}

		void DrawTriangles(int count) const;
		void DrawIndexed(int count) const;

		void ClearColorAndDepth() const;

		void InitOpenGL(int windowWidth, int windowHeight) const;

		void SetViewportSize(int windowWidth, int windowHeight) const
		{
			SetViewportSize(0, 0, windowWidth, windowHeight);
		}

		void SetViewportSize(int startX, int startY, int windowWidth, int windowHeight) const;
		
		void BindScreenFrameBuffer() const;

		enum class Option
		{
			DEPTH_TEST
		};

		void Enable(Option opt) const;
		void Disable(Option opt) const;
	private:
		OpenGLRenderAPI() = default;
	};
}
