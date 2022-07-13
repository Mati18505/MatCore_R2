#pragma once

namespace MatCore {
	struct TagComponent {
	public:
		TagComponent(std::string tag) :tag(tag) {}
		TagComponent(const TagComponent& other) : tag(tag) {}
		std::string Tag() { return tag; }
	private:
		std::string tag;
	};
}