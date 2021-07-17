//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_TEXTURE_H
#define TRACER_TEXTURE_H

#include <glad/gl.h>

#include "non_copyable.h"

class Texture : NonCopyable {
public:
    Texture(int width, int height);

    ~Texture();

    void upload(const float *data);

    void bind(GLuint unit);

private:
    int width;
    int height;
    GLuint texture = 0;
};

#endif //TRACER_TEXTURE_H
