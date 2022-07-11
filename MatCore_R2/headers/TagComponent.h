#pragma once

namespace MatCore {
	struct TagComponent {
	public:
		TagComponent(const char* tag) :tag(tag) {}
		TagComponent(const TagComponent& other) : tag(tag) {}
	private:
		const char* tag;
	};
}