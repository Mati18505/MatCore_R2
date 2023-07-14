#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec3 aNormal;

out VS_OUT
{
    vec2 uv;
} vs_out;

layout (std140, binding = 0) uniform Matrices
{
    mat4 mvp;
};

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
    vs_out.uv = aUV;
}  