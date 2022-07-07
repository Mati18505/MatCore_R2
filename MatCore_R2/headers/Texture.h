#pragma once

namespace MatCore {
	class Texture2D {
	public:
		Texture2D(const char* path);
		~Texture2D();
		unsigned int GetWidth() const { return width; }
		unsigned int GetHeight() const { return height; }
		void Bind(unsigned int slot = 0) const;
	private:
		unsigned int width, height;
		unsigned int renderID;
	};
}