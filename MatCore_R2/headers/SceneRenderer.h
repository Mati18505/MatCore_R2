#pragma once
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/Resource.h"
#include "OpenGL/MeshBuffer.h"
#include "OpenGL/ShaderProgram.h"
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

    private:
        void RenderScene(Scene& scene);
        void RenderEntity(MeshComponent& meshComponent, Transform& transform, Material& material, Camera& camera);

        Resource<FrameBuffer> frameBuffer;
        Resource<MeshBuffer> quad;
        Resource<ShaderProgram> screenShader;

        static std::vector<float> quadVertices;
        static std::vector<int> quadIndices;
    };
}
