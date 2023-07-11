#include "SceneRenderer.h"
#include "OpenGL/StaticRenderer.h"
#include "OpenGL/ShaderProgram.h"
#include "Application.h"
#include "MatCore.h"
#include "Cameras/Camera.h"
#include <glad/glad.h>
extern MatCore::Application* applicationP;

namespace MatCore {
    void SceneRenderer::Render(Scene& scene) {
        StaticRenderer::Get().SetViewportSize(applicationP->WindowWidth(), applicationP->WindowHeight());
        StaticRenderer::Get().ClearColorAndDepth();
        entt::registry& registry = scene.GetEntities();

        auto mainCameraOpt = scene.GetMainCamera();
        if (!mainCameraOpt)
            return;
        Camera mainCamera = mainCameraOpt.value();

        auto group = registry.group<>(entt::get<MeshComponent, Transform, Material>);
        for (auto entity : group)
        {
            MeshComponent& meshComponent = group.get<MeshComponent>(entity);
            Transform& transform = group.get<Transform>(entity);
            Material& material = group.get<Material>(entity);
            RenderEntity(meshComponent, transform, material, mainCamera);
        }
    }
    void SceneRenderer::RenderEntity(MeshComponent& meshComponent, Transform& transform, Material& material, Camera& camera) {
        StaticRenderer::Get().Bind(meshComponent.meshAsset.GetBuffer().get());
        StaticRenderer::Get().BindTexture(material.albedo, 0);

        glm::mat4 mvpMatrix = camera.GetProjection() * camera.GetView() * transform.GetGlobalModelMatrix();
        auto& s = material.shader.GetBuffer();
        StaticRenderer::Get().Bind(s.get());
        auto mvpUniformPos = glGetUniformLocation(s->GetHandle(), "mvp");
        glUniformMatrix4fv(mvpUniformPos, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

        StaticRenderer::Get().DrawIndexed((int)meshComponent.mesh.GetTriangles()->size());
    }
}