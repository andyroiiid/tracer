//
// Created by andyroiiid on 7/17/2021.
//

#include "realtime/quad_shader.h"

QuadShader::QuadShader() : Shader(R"GLSL(
#version 450 core
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexCoord;

layout(location = 0) out vec2 vTexCoord;

void main() {
    gl_Position = vec4(aPosition, 0.0, 1.0);
    vTexCoord = aTexCoord;
}
)GLSL", R"GLSL(
#version 450 core
layout(location = 0) in vec2 vTexCoord;

layout(location = 0) out vec4 fColor;

layout(binding = 0) uniform sampler2D uTexture;

vec3 ACESToneMapping(vec3 color)
{
	const float A = 2.51f;
	const float B = 0.03f;
	const float C = 2.43f;
	const float D = 0.59f;
	const float E = 0.14f;
	return (color * (A * color + B)) / (color * (C * color + D) + E);
}

void main() {
    vec3 color = texture(uTexture, vTexCoord).rgb;
    color = ACESToneMapping(color);
    fColor = vec4(color, 1.0);
}
)GLSL") {}
