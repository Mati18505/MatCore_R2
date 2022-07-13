#pragma once
#include "Scene.h"

#include "MeshComponent.h"
#include "Transform.h"
#include "material.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Log.h"
#include "Renderer.h"
#include "Entity.h"
#include "TagComponent.h"

MatCore::Scene::Scene() :camera(nullptr) {
    entitiesRegistry.on_construct<MeshComponent>().connect<&MeshRenderer::OnConstruct>();
    entitiesRegistry.on_destroy<MeshComponent>().connect<&MeshRenderer::OnDestroy>();
}

MatCore::Scene::~Scene() {
    
}

MatCore::Entity MatCore::Scene::CreateEntity(std::string name)
{
    Entity entity(this);
    entity.AddComponent<Transform>();
    if (name.empty()) name = "Untitled entity";
    entity.AddComponent<TagComponent>(name);
    return entity;
}

void MatCore::Scene::DestroyEntity(Entity entity)
{
    entitiesRegistry.destroy(entity);
    //TODO: usun¹æ w tym miejscu entity-dzieci
}