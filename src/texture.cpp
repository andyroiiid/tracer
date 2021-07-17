//
// Created by andyroiiid on 7/17/2021.
//

#include "texture.h"

Texture::Texture(int width, int height) : width(width), height(height) {
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glTextureStorage2D(texture, 1, GL_RGB32F, width, height);

    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

void Texture::upload(const float *data) { // NOLINT(readability-make-member-function-const)
    glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_FLOAT, data);
}

void Texture::bind(GLuint unit) { // NOLINT(readability-make-member-function-const)
    glBindTextureUnit(unit, texture);
}
