//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_QUAD_H
#define TRACER_QUAD_H

#include <glad/gl.h>

#include "non_copyable.h"
#include "quad_shader.h"

class Quad : NonCopyable {
public:
    Quad();

    ~Quad();

    void draw();

private:
    QuadShader shader;

    GLuint vbo = 0;
    GLuint vao = 0;
};

#endif //TRACER_QUAD_H
