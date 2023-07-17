#version 450 core
#define NUM_OF_POINT_LIGHTS 4

layout (location = 0) in VS_OUT
{
    vec2 uv;
    vec3 pos;
    vec3 normal;
} fs_in;

layout (location = 0) out vec4 FragColor;

struct DirectionalLight
{
    vec3 direction;
    vec3 color;
    float intensity;
};

struct PointLight
{
    vec3 position;
    float intensity;
    vec3 color;

    float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
    vec3 position;
    float intensity;
    vec3 direction;
    float cutOff;
    vec3 color; 
    float outerCutOff;

    float constant;
	float linear;
	float quadratic;
};

layout (std140, binding = 1) uniform Lights
{
    DirectionalLight directionalLight;
    PointLight pointLights[NUM_OF_POINT_LIGHTS];
    SpotLight spotLight;
} lights;

layout (std140, binding = 2) uniform fragData
{
    vec3 viewPos;
};

layout (binding = 0) uniform sampler2D diffuse;
layout (binding = 1) uniform sampler2D specular;

layout (std140, binding = 3) uniform MaterialData
{
    float shininess;
} material;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 norm, vec3 viewDir)
{
    vec3 ambient = light.color * texture(diffuse, fs_in.uv).rgb * 0.2;

    //diffuse
    vec3 lightDir = normalize(-light.direction);
    float diffuseStrenght = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrenght * light.color * texture(diffuse, fs_in.uv).rgb;

    //specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * light.color * texture(specular, fs_in.uv).rgb;

    ambient *= light.intensity;
    diffuse *= light.intensity;
    specular *= light.intensity;

    return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 norm, vec3 viewDir)
{
    vec3 ambient = light.color * texture(diffuse, fs_in.uv).rgb * 0.2;

    //diffuse
    vec3 lightDir = normalize(light.position - fs_in.pos);
    float diffuseStrenght = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrenght * light.color * texture(diffuse, fs_in.uv).rgb;

    //specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * light.color * texture(specular, fs_in.uv).rgb;;

    //attenuation
    float distance = length(light.position - fs_in.pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient = ambient * attenuation * light.intensity;
    diffuse = diffuse * attenuation * light.intensity;
    specular = specular * attenuation * light.intensity;

    return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 norm, vec3 viewDir)
{
    vec3 ambient = light.color * texture(diffuse, fs_in.uv).rgb * 0.2;

    vec3 lightDir = normalize(light.position - fs_in.pos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);  

    //diffuse
    float diffuseStrenght = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrenght * light.color * texture(diffuse, fs_in.uv).rgb;

    //specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * light.color * texture(specular, fs_in.uv).rgb;

    //attenuation
    float distance = length(light.position - fs_in.pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    //ambient attenuation?
    ambient *= light.intensity;
    diffuse = diffuse * attenuation * intensity * light.intensity;
    specular = specular * attenuation * intensity * light.intensity;

    return ambient + diffuse + specular;
}

void main() {
    vec3 norm = normalize(fs_in.normal);
    vec3 viewDir = normalize(viewPos - fs_in.pos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    
    result += CalculateDirectionalLight(lights.directionalLight, norm, viewDir);

    for(int i = 0; i < NUM_OF_POINT_LIGHTS; i++)
    {
        if(lights.pointLights[i].intensity > 0)
            result += CalculatePointLight(lights.pointLights[i], norm, viewDir);
    }

    result += CalculateSpotLight(lights.spotLight, norm, viewDir);

    FragColor = vec4(result, 1.0);
}