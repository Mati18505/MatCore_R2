#pragma once
#include <vector>
namespace MatCore {
	class Entity;
	struct InheritanceComponent {
	public:
		InheritanceComponent() = default;
		Entity parentEntity;
		std::vector<Entity> childEntities;
	};
}
