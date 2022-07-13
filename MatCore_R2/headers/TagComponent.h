#pragma once

namespace MatCore {
	struct TagComponent {
	public:
		TagComponent(std::string tag) :tag(tag) {}
		TagComponent(const TagComponent& other) : tag(tag) {}
		operator std::string () const { return tag; }
	private:
		std::string tag;
	};
}