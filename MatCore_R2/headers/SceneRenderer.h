#pragma once

namespace MatCore
{
    class Scene;
    struct MeshComponent;
    struct Transform;
    struct Material;
    class Camera;

    class SceneRenderer
    {
    public:
        void Render(Scene& scene);

    private:
        void RenderEntity(MeshComponent& meshComponent, Transform& transform, Material& material, Camera& camera);
    };
}
