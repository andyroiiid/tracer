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

void main() {
    fColor = texture(uTexture, vTexCoord);
}
)GLSL") {}
