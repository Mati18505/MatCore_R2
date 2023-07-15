#version 450 core

uniform sampler2D mtexture;

in VS_OUT
{
    vec2 uv;
} fs_in;

layout(location = 0) out vec4 FragColor;

void main() {
    FragColor = texture(mtexture, fs_in.uv);
}