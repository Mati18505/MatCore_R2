#pragma once
#include "Bindable.h"
#include <memory>
#include <string>
#include "OpenGL/GPUResource.h"

namespace MatCore {
	class Texture2D : public GPUResource {
	public:
		explicit Texture2D(const std::string& path);
		~Texture2D() override;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator= (Texture2D&&) = delete;

		unsigned int GetWidth() const { return width; }
		unsigned int GetHeight() const { return height; }
		void Bind(unsigned int slot = 0) const;
		void* GetRawHandle() { return (void*)ID; }
	private:
		uint32_t ID;
		uint32_t width;
		uint32_t height;
	};
}