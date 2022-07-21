#pragma once
#include "Scene.h"

#include "MeshComponent.h"
#include "Transform.h"
#include "material.h"
#include "CameraComponent.h"
#include "Application.h"
#include "Log.h"
#include "Renderer.h"
#include "Entity.h"
#include "TagComponent.h"
#include "InheritanceComponent.h"
#include "TransformSystem.h"

MatCore::Scene::Scene() {
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
    auto childs = IC.childEntities;
    for (Entity childEntity : childs)
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

void MatCore::Scene::FrameBufferSizeCallback(int width, int height)
{
    auto camera = GetMainRuntimeCamera().first;
    if (camera)
        camera->RecalculateProjectionMatrix(width, height);
}


std::pair<MatCore::SceneCamera*, MatCore::Entity> MatCore::Scene::GetMainRuntimeCamera()
{
    auto view = entitiesRegistry.view<CameraComponent>();

    for (auto entityH : view) {
        auto& cameraComponent = view.get<CameraComponent>(entityH);
        if (cameraComponent.primary == true)
            return { &cameraComponent.camera, Entity(entityH, this) };
    }
    return { nullptr, Entity::Null() };
}

std::optional<MatCore::Camera> MatCore::Scene::GetMainCamera()
{
    if (runtime)
    {
        SceneCamera* runtimeCamera = GetMainRuntimeCamera().first;
        if (runtimeCamera)
            return *runtimeCamera;
    }
    else
    {
#if 0
        if (editorCamera)
            return editorCamera;
#endif
    }
    return {};
}

#if 0
void MatCore::Scene::OnEditorUpdate()
{
    runtime = false;
}
#endif

void MatCore::Scene::OnRuntimeUpdate()
{
    runtime = true;
    //TODO: update scripts
    auto[camera, entity] = GetMainRuntimeCamera();
    if (camera) {
        camera->RecalculateViewMatrix(entity.GetComponent<Transform>());
        camera->RecalculateProjectionMatrix(applicationP->WindowWidth(), applicationP->WindowHeight());
    }
}