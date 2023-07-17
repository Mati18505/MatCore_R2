#pragma once
#include "OpenGL/UniformBuffer.h"
#include "Resource.h"
#include "glm/glm.hpp"
#include <entt.hpp>

namespace MatCore
{
    class LightRenderer
    {
    public:
        LightRenderer() = default;
        void UpdateData(entt::registry& registry);
        void BindToUniform(unsigned int slot);
    private:
        struct PointLight
        {
            glm::vec3 position; // 16 0, 12
            float intensity; // 4 12, 16
            glm::vec3 color; // 16 16, 28

            float constant; // 4 28, 32
            float linear; // 4 32, 36
            float quadratic; // 4 36, 40

            float padding; // 4 40, 44
            float padding2; // 4 44, 48
        };

        struct DirectionalLight
        {
            glm::vec3 direction; // 16 0, 12
            float padding; // 4 12, 16
            glm::vec3 color; // 16 16, 28
            float intensity; // 4 28, 32
        };

        struct SpotLight
        {
            glm::vec3 position; // 16 0, 12
            float intensity; // 4 12, 16
            glm::vec3 direction; // 16 16, 28
            float cutOff; // 4 28, 32
            glm::vec3 color; // 16 32, 44
            float outerCutOff; // 4 44, 48

            float constant; // 4 48, 52
            float linear; // 4 52, 56
            float quadratic; // 4 56, 60

            float padding; // 4 56, 64
        };

        struct Lights
        {
            DirectionalLight directionalLight{};
            std::array<PointLight, 4> pointLights{};
            SpotLight spotLight{};
        };
        Lights lightsCB{};

        Resource<UniformBufferT<Lights>> lights{std::make_shared<UniformBufferT<Lights>>()};

        void SetDirectionalLight(entt::registry& registry);
        void SetPointLights(entt::registry& registry);
        void SetSpotLight(entt::registry& registry);
    };
};