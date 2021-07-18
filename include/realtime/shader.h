//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_SHADER_H
#define TRACER_SHADER_H

#include <string>
#include <glad/gl.h>

#include "non_copyable.h"

class Shader : NonCopyable {
public:
    Shader(const std::string &vertexSource, const std::string &fragmentSource);

    ~Shader();

    void use();

protected:
    static GLuint createShader(GLenum type, const char *source);

    static GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

    GLuint program = 0;
};

#endif //TRACER_SHADER_H
