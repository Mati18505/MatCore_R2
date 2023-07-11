#pragma once
#include "Renderer.h"
#include <glad/glad.h>
#include "Mesh.h"
#include "Transform.h"
#include "Material.h"
#include "Cameras/Camera.h"
#include "Scene.h"
#include "Application.h"
#include "Log.h"
#include "OpenGL/StaticRenderer.h"
#include "MeshComponent.h"

void MatCore::Renderer::RenderScene(){
    StaticRenderer::Get().SetViewportSize(applicationP->windowWidth, applicationP->windowHeight);

    auto mainCameraOpt = applicationP->scene->GetMainCamera();
    if (!mainCameraOpt.has_value())
        return;
    Camera mainCamera = mainCameraOpt.value();

    vertices = triangles = drawCalls = 0;
    auto group = applicationP->scene->entitiesRegistry.group<>(entt::get<MeshComponent, Transform, Material>);
    for (auto entity : group)
    {
        MeshComponent& meshComponent = group.get<MeshComponent>(entity);
        Transform& transform = group.get<Transform>(entity);
        Material& material = group.get<Material>(entity);
        MeshRenderer::RenderMesh(meshComponent, transform, material, mainCamera);
        vertices += meshComponent.mesh.GetVertices()->size();
        triangles += meshComponent.mesh.GetTriangles()->size();
        drawCalls++;
    }
}

void MatCore::MeshRenderer::RenderMesh(MeshComponent& meshComponent, Transform& transform, Material& material, Camera& camera) {

    material.SetUniforms();
    material.SetMVPMatrix(transform.GetGlobalModelMatrix(), camera.GetProjection() * camera.GetView());
    material.SetSelfUniforms();
}