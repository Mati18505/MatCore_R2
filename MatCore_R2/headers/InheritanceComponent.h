#pragma once
#include "Entity.h"
namespace MatCore {
	struct InheritanceComponent {
	public:
		InheritanceComponent() = default;
		Entity parentEntity;
		std::vector<Entity> childEntities;
	};
}
