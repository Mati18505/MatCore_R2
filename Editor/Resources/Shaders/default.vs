#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec3 aNormal;

layout (location = 0) out VS_OUT
{
    vec2 uv;
    vec3 pos;
    vec3 normal;
} vs_out;

layout (std140, binding = 0) uniform Matrices
{
    mat4 mvp;
    mat4 normalMatrix;
    mat4 model;
};

void main()
{
    vs_out.pos = vec3(model * vec4(aPos, 1.0));
    vs_out.normal = vec3(normalMatrix * vec4(aNormal, 0.0));
    vs_out.uv = aUV;
    gl_Position = mvp * vec4(aPos, 1.0);
}  