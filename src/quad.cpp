//
// Created by andyroiiid on 7/17/2021.
//

#include "quad.h"

struct Vertex {
    glm::vec2 aPosition;
    glm::vec2 aTexCoord;
};

Quad::Quad() {
    glCreateBuffers(1, &vbo);
    constexpr Vertex vertices[] = {
            {glm::vec2{-1.0f, -1.0f}, glm::vec2{0.0f, 0.0f}},
            {glm::vec2{1.0f, -1.0f},  glm::vec2{1.0f, 0.0f}},
            {glm::vec2{-1.0f, 1.0f},  glm::vec2{0.0f, 1.0f}},
            {glm::vec2{1.0f, 1.0f},   glm::vec2{1.0f, 1.0f}}
    };
    glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, aPosition));

    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayAttribBinding(vao, 1, 0);
    glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, aTexCoord));
}

Quad::~Quad() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Quad::draw() {
    shader.use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}
