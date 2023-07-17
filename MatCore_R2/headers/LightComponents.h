#pragma once
#include "glm/glm.hpp"

struct DirectionalLightComponent
{
	glm::vec3 color {1.0f, 1.0f, 1.0f};
	float intensity = 1;
};

struct PointLightComponent
{
	glm::vec3 color {1.0f, 1.0f, 1.0f};
	float intensity = 1;

	float constant = 1.0f;
	float linear = 0.027f;
	float quadratic = 0.0028f;
};

struct SpotLightComponent
{
	glm::vec3 color {1.0f, 1.0f, 1.0f};
	float intensity = 1;
	float cutOffDegrees = 40;
	float outerCutOffDegrees = 45;

	float constant = 1.0f;
	float linear = 0.007f;
	float quadratic = 0.0002f;
};