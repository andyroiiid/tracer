//
// Created by andyroiiid on 7/17/2021.
//

#include "interactive_renderer.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void InteractiveRenderer::resizeWindow(int newWidth, int newHeight) {
    windowWidth = newWidth;
    windowHeight = newHeight;
    resourcesDirty = true;
}

void InteractiveRenderer::update() {
    if (resourcesDirty) {
        recreateResources(windowWidth / downScale, windowHeight / downScale);
    }

    if (cameraDirty) {
        recreateCamera();
    }

    if (nextIteration > iterationTarget) return;

    pathTracer->sample(camera, world, nextIteration, maxDepth);
    texture->upload(pathTracer->getImage().data());

    nextIteration++;
}

void InteractiveRenderer::draw() {
    texture->bind(0);
    quad.draw();
    glBindTextureUnit(0, 0);
}

void InteractiveRenderer::ui() {
    if (ImGui::SliderInt("down scale", &downScale, 1, 10)) {
        resourcesDirty = true;
    }

    ImGui::LabelText("next iteration", "%d", nextIteration);
    if (ImGui::SliderInt("iteration target", &iterationTarget, 1, 256)) {
        if (iterationTarget < nextIteration) resetIteration();
    }

    if (ImGui::SliderInt("max depth", &maxDepth, 1, 64)) {
        resetIteration();
    }

    if (ImGui::CollapsingHeader("camera")) {
        if (ImGui::InputFloat3("position", glm::value_ptr(cameraPosition))) {
            cameraDirty = true;
        }
        if (ImGui::SliderAngle("fov", &cameraFoV, 1.0f, 179.0f)) {
            cameraDirty = true;
        }
        if (ImGui::SliderFloat("aperture", &cameraAperture, 0.0f, 1.0f)) {
            cameraDirty = true;
        }
        if (ImGui::SliderFloat("focus distance", &cameraFocusDistance, 0.1f, 10.0f)) {
            cameraDirty = true;
        }
    }
}

void InteractiveRenderer::recreateResources(int width, int height) {
    texture = std::make_unique<Texture>(width, height);
    pathTracer = std::make_unique<PathTracer>(width, height);

    recreateCamera();

    resourcesDirty = false;
}

void InteractiveRenderer::recreateCamera() {
    constexpr glm::vec3 target{0.0f, 0.0f, 0.0f};
    constexpr glm::dvec3 up{0.0, 1.0, 0.0};

    camera = Camera(
            cameraPosition, target, up,
            cameraFoV,
            double(windowWidth) / double(windowHeight),
            cameraAperture,
            cameraFocusDistance
    );

    resetIteration();

    cameraDirty = false;
}
