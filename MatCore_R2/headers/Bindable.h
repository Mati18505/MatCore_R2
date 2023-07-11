#pragma once

namespace MatCore
{
	class Bindable {
	public:
		virtual ~Bindable() = default;
		virtual void Bind() const = 0;
	};
}
