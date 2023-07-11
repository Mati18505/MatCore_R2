#pragma once
#include <memory>
#include <type_traits>
#include "GPUResource.h"

namespace MatCore
{
	template<typename T>
	class Resource {
	public:
		explicit Resource(std::shared_ptr<T> buffer)
			:buffer(buffer)
		{
			static_assert(std::is_base_of<GPUResource, T>::value, "T must inherit from GPUResource");
		}

		const std::shared_ptr<T>& GetBuffer() const { return buffer; }

	private:
		std::shared_ptr<T> buffer;
	};
}