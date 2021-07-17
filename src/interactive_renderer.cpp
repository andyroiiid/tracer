//
// Created by andyroiiid on 7/17/2021.
//

#include "interactive_renderer.h"

void InteractiveRenderer::resize(int width, int height) {
    texture = std::make_unique<Texture>(width, height);
    pathTracer = std::make_unique<PathTracer>(width, height, 32);

    constexpr glm::dvec3 position{2.0, 2.0, 2.0};
    constexpr glm::dvec3 target{0.0, 0.0, 0.0};
    constexpr glm::dvec3 up{0.0, 1.0, 0.0};
    camera = Camera(
            position, target, up,
            45.0,
            double(width) / double(height),
            0.2,
            glm::length(target - position)
    );

    clearSamples();
}

void InteractiveRenderer::updateSamples(int iterationTarget) {
    if (iteration > iterationTarget) return;

    pathTracer->sample(camera, world, iteration);
    texture->upload(pathTracer->getImage().data());

    iteration++;
}

void InteractiveRenderer::draw() {
    texture->bind(0);
    quad.draw();
    glBindTextureUnit(0, 0);
}
