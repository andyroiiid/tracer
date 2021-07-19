//
// Created by andyroiiid on 7/17/2021.
//

#include "realtime/interactive_renderer.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

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
        glm::vec3 forward{-glm::cos(cameraYaw), 0.0f, -glm::sin(cameraYaw)};
        glm::vec3 right{-glm::sin(cameraYaw), 0.0f, glm::cos(cameraYaw)};
        glm::vec3 up{0.0f, 1.0f, 0.0f};

        float moveSpeed = 5.0f * float(deltaTime);

        if (glfwGetKey(window, GLFW_KEY_W)) {
            cameraPosition += forward * moveSpeed;
            cameraDirty = true;
        }
        if (glfwGetKey(window, GLFW_KEY_S)) {
            cameraPosition -= forward * moveSpeed;
            cameraDirty = true;
        }
        if (glfwGetKey(window, GLFW_KEY_A)) {
            cameraPosition += right * moveSpeed;
            cameraDirty = true;
        }
        if (glfwGetKey(window, GLFW_KEY_D)) {
            cameraPosition -= right * moveSpeed;
            cameraDirty = true;
        }
        if (glfwGetKey(window, GLFW_KEY_E)) {
            cameraPosition += up * moveSpeed;
            cameraDirty = true;
        }
        if (glfwGetKey(window, GLFW_KEY_Q)) {
            cameraPosition -= up * moveSpeed;
            cameraDirty = true;
        }

        double currXPos, currYPos;
        glfwGetCursorPos(window, &currXPos, &currYPos);

        auto deltaXPos = float(currXPos - prevXPos) * 0.002f;
        auto deltaYPos = float(currYPos - prevYPos) * 0.002f;
        if (deltaXPos != 0.0) {
            cameraYaw = cameraYaw + deltaXPos;
            cameraDirty = true;
        }
        if (deltaYPos != 0.0) {
            cameraPitch = glm::clamp(cameraPitch + deltaYPos, glm::radians(-89.9f), glm::radians(89.9f));
            cameraDirty = true;
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
        if (cameraDirty) {
            recreateCamera();
        }

        if (nextIteration > iterationTarget) return;

        renderFuture = executor.async([this] {
            pathTracer->sample(camera, world, nextIteration, maxDepth);
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

    if (ImGui::SliderInt("max depth", &maxDepth, 1, 64)) {
        resetIteration();
    }

    if (ImGui::CollapsingHeader("camera")) {
        if (ImGui::InputFloat3("position", glm::value_ptr(cameraPosition))) {
            cameraDirty = true;
        }
        if (ImGui::SliderAngle("yaw", &cameraYaw, 0.0f, 360.0f)) {
            cameraDirty = true;
        }
        if (ImGui::SliderAngle("pitch", &cameraPitch, -89.9f, 89.9f)) {
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

    if (ImGui::CollapsingHeader("world")) {
        if (world.ui()) {
            resetIteration();
        }
    }
}

void InteractiveRenderer::recreateResources(int width, int height) {
    texture = std::make_unique<Texture>(width, height);
    pathTracer = std::make_unique<PathTracer>(executor, width, height);

    recreateCamera();

    resourcesDirty = false;
}

void InteractiveRenderer::recreateCamera() {
    glm::vec3 forward = glm::vec3{
            glm::cos(cameraPitch) * glm::cos(cameraYaw),
            glm::sin(cameraPitch),
            glm::cos(cameraPitch) * glm::sin(cameraYaw)
    };

    constexpr glm::dvec3 up{0.0, 1.0, 0.0};

    camera = Camera(
            cameraPosition, forward, up,
            cameraFoV,
            double(windowWidth) / double(windowHeight),
            cameraAperture,
            cameraFocusDistance
    );

    resetIteration();

    cameraDirty = false;
}
