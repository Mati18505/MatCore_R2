#pragma once
#include "OpenGL/FrameBuffer.h"
#include "Resource.h"
#include "OpenGL/MeshBuffer.h"
#include "OpenGL/ShaderProgram.h"
#include "OpenGL/UniformBuffer.h"
#include "LightRenderer.h"

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
        LightRenderer lightRenderer;

        struct ObjectCB
        {
            glm::mat4 mvp;
            glm::mat4 normalMatrix;
            glm::mat4 model;
        };
        ObjectCB objectCB{};
        Resource<UniformBufferT<ObjectCB>> objectUB{std::make_shared<UniformBufferT<ObjectCB>>()};

        struct FragDataCB
        {
            glm::vec3 viewPos;
            float padding;
        };
        FragDataCB fragDataCB{};
        Resource<UniformBufferT<FragDataCB>> fragDataUB{std::make_shared<UniformBufferT<FragDataCB>>()};
        
        struct MaterialDataCB
        {
            float shininess = 64;
        };
        MaterialDataCB materialDataCB{};
        Resource<UniformBufferT<MaterialDataCB>> materialDataUB{std::make_shared<UniformBufferT<MaterialDataCB>>()};

        static std::vector<float> quadVertices;
        static std::vector<int> quadIndices;
    };
}
