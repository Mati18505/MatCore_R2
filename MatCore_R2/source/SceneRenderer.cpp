#include "pch.h"

#include "SceneRenderer.h"
#include "OpenGL/OpenGLRenderAPI.h"
#include "OpenGL/ShaderProgram.h"
#include "Application.h"
#include "MatCore.h"
#include "Cameras/Camera.h"
#include "Application.h"
#include <glad/glad.h>
#include "Factory.h"

extern MatCore::Application* applicationP;
    
namespace MatCore {
    std::vector<float> SceneRenderer::quadVertices{
        -1.0f,  1.0f, 0.0f, 1.0f,         // Top left
         1.0f,  1.0f, 1.0f, 1.0f,         // Top Right
        -1.0f, -1.0f, 0.0f, 0.0f,         // Bottom left
         1.0f, -1.0f, 1.0f, 0.0f          // Bottom right
    };
    std::vector<int> SceneRenderer::quadIndices{
        2, 1, 0,
        2, 3, 1
    };

    SceneRenderer::SceneRenderer()
        : frameBuffer(std::make_shared<FrameBuffer>(applicationP->WindowWidth(), applicationP->WindowHeight()))
    {
        auto vs = Factory::Get().CreateShaderAssetFromFile("Resources/Shaders/Screen.vs", Shader::ShaderType::vertex);
        auto fs = Factory::Get().CreateShaderAssetFromFile("Resources/Shaders/Screen.fs", Shader::ShaderType::fragment);
        screenShader = Factory::Get().CreateShaderProgramAssetFromShaders(vs, fs);

        quad = Resource<MeshBuffer>(std::make_shared<MeshBuffer>());
        BufferLayout layout;
        layout.Push(BufferLayout::Type::Float, 2);//pos
        layout.Push(BufferLayout::Type::Float, 2);//uv
        quad.GetBuffer()->SetLayout(layout);
        quad.GetBuffer()->UpdateT(quadVertices, quadIndices);
    }
    void SceneRenderer::Render(Scene& scene) {
        auto& renderer = OpenGLRenderAPI::Get();
        renderer.Bind(frameBuffer);
        renderer.Enable(OpenGLRenderAPI::Option::DEPTH_TEST);
        renderer.SetViewportSize(applicationP->WindowWidth(), applicationP->WindowHeight());
        renderer.ClearColorAndDepth();

        RenderScene(scene);

        renderer.BindScreenFrameBuffer();
        renderer.Disable(OpenGLRenderAPI::Option::DEPTH_TEST);
        renderer.ClearColorAndDepth();
        renderer.Bind(screenShader);
        renderer.Bind(quad);
        frameBuffer.GetBuffer().get()->BindTexture();
        renderer.DrawIndexed(6);

    }
    
    void SceneRenderer::RenderScene(Scene& scene)
    {
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
        OpenGLRenderAPI::Get().Bind(meshComponent.meshAsset);
        OpenGLRenderAPI::Get().BindTexture(material.albedo, 0);

        auto& s = material.shader.GetBuffer();
        OpenGLRenderAPI::Get().Bind(s.get());

        cb.mvp = camera.GetProjection() * camera.GetView() * transform.GetGlobalModelMatrix();
        ub.GetBuffer()->Update(cb);
        ub.GetBuffer()->Bind(0);

        OpenGLRenderAPI::Get().DrawIndexed((int)meshComponent.mesh.GetTriangles()->size());
    }

    void SceneRenderer::FrameBufferSizeCallback(int width, int height)
    {
        frameBuffer.SetBuffer(std::make_shared<FrameBuffer>(width, height));
    }
}