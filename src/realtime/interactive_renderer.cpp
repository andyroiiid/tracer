//
// Created by andyroiiid on 7/17/2021.
//

#include "realtime/interactive_renderer.h"

#include <imgui.h>

void InteractiveRenderer::resizeWindow(int newWidth, int newHeight) {
    windowWidth = newWidth;
    windowHeight = newHeight;
    resourcesDirty = true;
}

void InteractiveRenderer::update(double deltaTime) {
    if (input.update()) {
        glm::dvec3 direction{
                input.axisRight(),
                input.axisUp(),
                input.axisForward()
        };
        if (direction.x != 0.0 || direction.y != 0.0 || direction.z != 0.0) {
            glm::dvec3 forward = camera.forward();
            glm::dvec3 right = camera.right();
            constexpr glm::dvec3 up{0.0, 1.0, 0.0};
            direction = glm::normalize(direction.x * right + direction.y * up + direction.z * forward);
            camera.move(direction * 5.0 * deltaTime);
        }

        double turn = input.axisTurn();
        if (turn != 0.0) {
            camera.rotateYaw(turn);
        }

        double lookUp = input.axisLookUp();
        if (lookUp != 0.0) {
            camera.rotatePitch(lookUp);
        }
    }

    if (renderFuture.valid()) {
        if (renderFuture.wait_for(std::chrono::microseconds(1)) == std::future_status::ready) {
            renderFuture.get();
            texture->upload(pathTracer->getImage().data());
            nextIteration++;
        }
    } else {
        // only recreate resources when not rendering
        if (resourcesDirty) {
            recreateResources(windowWidth / downScale, windowHeight / downScale);
        }
        if (camera.checkRecreate(windowWidth, windowHeight)) {
            resetIteration();
        }

        if (nextIteration > iterationTarget) return;

        renderFuture = executor.async([this] {
            pathTracer->sample(camera.getCamera(), world, nextIteration, maxDepth);
        });
    }
}

void InteractiveRenderer::draw() {
    texture->bind(0);
    quad.draw();
    glBindTextureUnit(0, 0);
}

void InteractiveRenderer::ui() {
    if (ImGui::Button("save")) {
        pathTracer->getImage().writeFile("output.png");
    }

    if (ImGui::SliderInt("down scale", &downScale, 1, 10)) {
        resourcesDirty = true;
    }

    ImGui::LabelText("next iteration", "%d", nextIteration);
    if (ImGui::SliderInt("iteration target", &iterationTarget, 1, 256)) {
        if (iterationTarget < nextIteration) resetIteration();
    }

    if (ImGui::SliderInt("max depth", &maxDepth, 1, 32)) {
        resetIteration();
    }

    camera.ui();

    if (ImGui::CollapsingHeader("world")) {
        if (world.ui()) {
            resetIteration();
        }
    }
}

void InteractiveRenderer::recreateResources(int width, int height) {
    texture = std::make_unique<Texture>(width, height);
    pathTracer = std::make_unique<PathTracer>(executor, width, height);
    camera.markDirty();
    resourcesDirty = false;
}
