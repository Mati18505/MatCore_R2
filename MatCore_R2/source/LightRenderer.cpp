#include "pch.h"
#include "LightRenderer.h"
#include "MatCore.h"

namespace MatCore {
	void LightRenderer::UpdateData(entt::registry& registry)
	{
        SetDirectionalLight(registry);
        SetPointLights(registry);
        SetSpotLight(registry);
        lights.GetBuffer()->Update(lightsCB);
	}
    
    void LightRenderer::BindToUniform(unsigned int slot)
    {
        lights.GetBuffer()->Bind(slot);
    }
    
    void LightRenderer::SetDirectionalLight(entt::registry& registry)
    {
        auto& lightsGroup = registry.group<>(entt::get<DirectionalLightComponent, Transform>);
        if (!lightsGroup.empty())
        {
            Transform& transform = lightsGroup.get<Transform>(lightsGroup[0]);
            DirectionalLightComponent& light = lightsGroup.get<DirectionalLightComponent>(lightsGroup[0]);
            lightsCB.directionalLight.direction = transform.GetLocalForwardVector();
            lightsCB.directionalLight.color = light.color;
            lightsCB.directionalLight.intensity = light.intensity;
        }
    }

    void LightRenderer::SetPointLights(entt::registry& registry)
    {
        auto& lightsGroup = registry.group<>(entt::get<PointLightComponent, Transform>);

        int i = 0;
        for (auto& pointLight : lightsGroup)
        {
            Transform& transform = lightsGroup.get<Transform>(pointLight);
            PointLightComponent& light = lightsGroup.get<PointLightComponent>(pointLight);
            lightsCB.pointLights[i].color = light.color;
            lightsCB.pointLights[i].position = transform.position;
            lightsCB.pointLights[i].intensity = light.intensity;
            lightsCB.pointLights[i].linear = light.linear;
            lightsCB.pointLights[i].quadratic = light.quadratic;
            i++;
        }
    }

    void LightRenderer::SetSpotLight(entt::registry& registry)
    {
        auto& lightsGroup = registry.group<>(entt::get<SpotLightComponent, Transform>);

        if (!lightsGroup.empty())
        {
            Transform& transform = lightsGroup.get<Transform>(lightsGroup[0]);
            SpotLightComponent& light = lightsGroup.get<SpotLightComponent>(lightsGroup[0]);

            lightsCB.spotLight.color = light.color;
            lightsCB.spotLight.direction = transform.GetLocalForwardVector();
            lightsCB.spotLight.intensity = light.intensity;
            lightsCB.spotLight.position = transform.position;
            lightsCB.spotLight.cutOff = glm::cos(glm::radians(light.cutOffDegrees));
            lightsCB.spotLight.outerCutOff = glm::cos(glm::radians(light.outerCutOffDegrees));
            lightsCB.spotLight.linear = light.linear;
            lightsCB.spotLight.quadratic = light.quadratic;
        }
    }
};