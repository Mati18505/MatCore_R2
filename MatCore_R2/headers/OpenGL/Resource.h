#pragma once
#include <memory>
#include <type_traits>
#include "GPUResource.h"

namespace MatCore
{
	template<typename T>
	class Resource {
	public:
		Resource() = default;
		explicit Resource(std::shared_ptr<T> buffer)
			:buffer(buffer)
		{
			static_assert(std::is_base_of<GPUResource, T>::value, "T must inherit from GPUResource");
		}

		void SetBuffer(std::shared_ptr<T> buffer) {
			this->buffer = buffer;
		}
		const std::shared_ptr<T>& GetBuffer() const { 
			if(!buffer)
				throw std::exception("Buffer was nullptr!");
			return buffer;
		}

	private:
		std::shared_ptr<T> buffer;
	};
}