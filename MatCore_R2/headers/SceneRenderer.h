#pragma once
#include "OpenGL/FrameBuffer.h"
#include "Resource.h"
#include "OpenGL/MeshBuffer.h"
#include "OpenGL/ShaderProgram.h"
#include "OpenGL/UniformBuffer.h"
#include <memory>


namespace MatCore
{
    class Scene;
    struct MeshComponent;
    struct Transform;
    struct Material;
    class Camera;
    class Factory;

    class SceneRenderer
    {
    public:
        SceneRenderer();
        void Render(Scene& scene);
        void FrameBufferSizeCallback(int width, int height);

    private:
        void RenderScene(Scene& scene);
        void RenderEntity(MeshComponent& meshComponent, Transform& transform, Material& material, Camera& camera);

        Resource<FrameBuffer> frameBuffer;
        Resource<MeshBuffer> quad;
        Resource<ShaderProgram> screenShader;

        struct CB
        {
            glm::mat4 mvp;
        };
        CB cb{};
        Resource<UniformBufferT<CB>> ub{std::make_shared<UniformBufferT<CB>>()};

        static std::vector<float> quadVertices;
        static std::vector<int> quadIndices;
    };
}
