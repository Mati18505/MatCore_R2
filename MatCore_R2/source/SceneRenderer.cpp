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
#include <glm/gtc/matrix_inverse.hpp>
#include "LightComponents.h"

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
        auto mainCameraOpt = scene.GetMainCamera();
        if (!mainCameraOpt)
            return;
        Camera mainCamera = mainCameraOpt.value();

        entt::registry& registry = scene.GetEntities();
        lightRenderer.UpdateData(registry);

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
        OpenGLRenderAPI::Get().BindTexture(material.specular, 1);

        auto& s = material.shader.GetBuffer();
        OpenGLRenderAPI::Get().Bind(s.get());

        objectCB.mvp = camera.GetProjection() * camera.GetView() * transform.GetGlobalModelMatrix();
        objectCB.model = transform.GetGlobalModelMatrix();
        objectCB.normalMatrix = glm::inverseTranspose(objectCB.model);
        objectUB.GetBuffer()->Update(objectCB);
        objectUB.GetBuffer()->Bind(0);

        lightRenderer.BindToUniform(1);

        fragDataCB.viewPos = glm::vec3(glm::inverse(camera.GetView())[3]);
        fragDataUB.GetBuffer()->Update(fragDataCB);
        fragDataUB.GetBuffer()->Bind(2);

        materialDataUB.GetBuffer()->Update(materialDataCB);
        materialDataUB.GetBuffer()->Bind(3);

        OpenGLRenderAPI::Get().DrawIndexed((int)meshComponent.mesh.GetTriangles()->size());
    }

    void SceneRenderer::FrameBufferSizeCallback(int width, int height)
    {
        frameBuffer.SetBuffer(std::make_shared<FrameBuffer>(width, height));
    }
}