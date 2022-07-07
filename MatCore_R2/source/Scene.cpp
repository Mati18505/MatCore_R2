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

MatCore::Scene::Scene() :camera(nullptr) {
    entitiesRegistry.on_construct<MeshComponent>().connect<&MeshRenderer::OnConstruct>();
    entitiesRegistry.on_destroy<MeshComponent>().connect<&MeshRenderer::OnDestroy>();
}

MatCore::Scene::~Scene() {
    
}