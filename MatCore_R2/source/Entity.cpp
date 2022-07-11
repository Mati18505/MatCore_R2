#include "Entity.h"
#include "Scene.h"

namespace MatCore {
    Entity::Entity(Scene* scene)
        :scene(scene)
    {
        entityHandle = scene->entitiesRegistry.create();
    }
}
