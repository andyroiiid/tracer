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

void InteractiveRenderer::startMoving(GLFWwindow *window) {
    moving = true;
    glfwGetCursorPos(window, &prevXPos, &prevYPos);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InteractiveRenderer::stopMoving(GLFWwindow *window) {
    moving = false;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void InteractiveRenderer::update(double deltaTime, GLFWwindow *window) {
    if (moving) {
        glm::dvec3 forward = camera.forward();
        glm::dvec3 right = camera.right();
        constexpr glm::dvec3 up{0.0, 1.0, 0.0};

        double moveSpeed = 5.0 * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_W)) {
            camera.move(-forward * moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_S)) {
            camera.move(forward * moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_A)) {
            camera.move(right * moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_D)) {
            camera.move(-right * moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_E)) {
            camera.move(up * moveSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_Q)) {
            camera.move(-up * moveSpeed);
        }

        double currXPos, currYPos;
        glfwGetCursorPos(window, &currXPos, &currYPos);

        double deltaYaw = (currXPos - prevXPos) * 0.002;
        double deltaPitch = (currYPos - prevYPos) * 0.002;
        if (deltaYaw != 0.0) {
            camera.rotateYaw(deltaYaw);
        }
        if (deltaPitch != 0.0) {
            camera.rotatePitch(deltaPitch);
        }

        prevXPos = currXPos;
        prevYPos = currYPos;
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
