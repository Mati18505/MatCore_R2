#pragma once
#include "Scene.h"

#include "MeshComponent.h"
#include "Transform.h"
#include "material.h"
#include "Camera.h"
#include "Application.h"
#include "Log.h"
#include "Renderer.h"
#include "Entity.h"
#include "TagComponent.h"
#include "InheritanceComponent.h"
#include "TransformSystem.h"

MatCore::Scene::Scene() :camera(nullptr) {
    entitiesRegistry.on_construct<MeshComponent>().connect<&MeshRenderer::OnConstruct>();
    entitiesRegistry.on_destroy<MeshComponent>().connect<&MeshRenderer::OnDestroy>();
}

MatCore::Scene::~Scene() {
    
}

MatCore::Entity MatCore::Scene::CreateEntity(std::string name, Entity parent)
{
    Entity entity(entitiesRegistry.create(), this);
    entity.AddComponent<Transform>();
    if (name.empty()) name = "Untitled entity";
    entity.AddComponent<TagComponent>(name);
    entity.AddComponent<InheritanceComponent>().parentEntity = parent;
    if (parent)
        parent.GetComponent<InheritanceComponent>().childEntities.push_back(entity);
    
    return entity;
}
MatCore::Entity MatCore::Scene::CreateEntity(std::string name)
{
    return CreateEntity(name, Entity::Null());
}

void MatCore::Scene::DestroyEntity(Entity entity)
{
    DestroyEntityChildrens(entity);
    EraseEntityFromHisParent(entity);
    entitiesRegistry.destroy(entity);
}

void MatCore::Scene::DestroyEntityChildrens(Entity entity)
{
    InheritanceComponent& IC = entity.GetComponent<InheritanceComponent>();
    for (Entity childEntity : IC.childEntities)
        DestroyEntity(childEntity);
}

void MatCore::Scene::EraseEntityFromHisParent(Entity entity)
{
    InheritanceComponent& IC = entity.GetComponent<InheritanceComponent>();
    if (IC.parentEntity != Entity::Null())
    {
        auto& childs = IC.parentEntity.GetComponent<InheritanceComponent>().childEntities;
        for (int i = 0; i < childs.size(); i++)
        {
            if (childs[i] == entity) {
                childs.erase(childs.begin() + i);
                break;
            }
        }
    }
}

void MatCore::Scene::BaseUpdate()
{
    TransformSystem::UpdateAllTransforms();
}