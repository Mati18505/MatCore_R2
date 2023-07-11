#pragma once
#include "Bindable.h"
#include <functional>
#include "TextureBuffer.h"
#include "Resource.h"

namespace MatCore
{
	class StaticRenderer
	{
	public:
		static StaticRenderer& Get()
		{
			static StaticRenderer r;
			return r;
		}

		void Bind(const Bindable* bindable) const
		{
			bindable->Bind();
		}

		void BindTexture(const Resource<Texture2D> texture, int slot) const
		{
			texture.GetBuffer()->Bind(slot);
		}

		void DrawIndexed(int count) const;

		void ClearColorAndDepth() const;

		void InitOpenGL(int windowWidth, int windowHeight) const;

		void SetViewportSize(int windowWidth, int windowHeight) const
		{
			SetViewportSize(0, 0, windowWidth, windowHeight);
		}

		void SetViewportSize(int startX, int startY, int windowWidth, int windowHeight) const;
	};
}
