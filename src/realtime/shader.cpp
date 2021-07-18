//
// Created by andyroiiid on 7/17/2021.
//

#include "realtime/shader.h"

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) {
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSource.c_str());
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
    program = createProgram(vertexShader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(program);
}

void Shader::use() { // NOLINT(readability-make-member-function-const)
    glUseProgram(program);
}

GLuint Shader::createShader(GLenum type, const char *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileStatus = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        GLint infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog);
        printf("failed to load shader: %s\n", infoLog);
        delete[] infoLog;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint Shader::createProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linkStatus = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        GLint infoLogLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto infoLog = new GLchar[infoLogLength];
        printf("failed to link program: %s\n", infoLog);
        delete[] infoLog;
        glDeleteProgram(program);
        return 0;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return program;
}