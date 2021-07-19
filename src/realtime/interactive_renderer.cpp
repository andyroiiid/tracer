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
        glm::dvec3 forward{glm::sin(cameraYaw), 0.0, -glm::cos(cameraYaw)};
        glm::dvec3 right{glm::cos(cameraYaw), 0.0, glm::sin(cameraYaw)};
        constexpr glm::dvec3 up{0.0, 1.0, 0.0};

        double moveSpeed = 5.0 * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_W)) {
            cameraPosition -= forward * moveSpeed;
            cameraDirty = true;
        }
        if (glfwGetKey(window, GLFW_KEY_S)) {
            cameraPosition += forward * moveSpeed;
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

        double deltaXPos = (currXPos - prevXPos) * 0.002;
        double deltaYPos = (currYPos - prevYPos) * 0.002;
        if (deltaXPos != 0.0) {
            cameraYaw = cameraYaw + deltaXPos;
            constexpr auto two_pi = glm::two_pi<double>();
            if (cameraYaw > two_pi) {
                cameraYaw -= two_pi;
            } else if (cameraYaw < 0.0) {
                cameraYaw += two_pi;
            }
            cameraDirty = true;
        }
        if (deltaYPos != 0.0) {
            cameraPitch = glm::clamp(cameraPitch + deltaYPos, glm::radians(-89.9), glm::radians(89.9));
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

    if (ImGui::SliderInt("max depth", &maxDepth, 1, 32)) {
        resetIteration();
    }

    if (ImGui::CollapsingHeader("camera")) {
        ImGui::LabelText("position", "%.2f, %.2f, %.2f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        ImGui::LabelText("yaw", "%f", glm::degrees(cameraYaw));
        ImGui::LabelText("pitch", "%f", glm::degrees(cameraPitch));

        if (ImGui::SliderAngle("fov", &cameraFoV, 1.0f, 179.0f)) {
            cameraDirty = true;
        }
        if (ImGui::SliderFloat("aperture", &cameraAperture, 0.0f, 1.0f)) {
            cameraDirty = true;
        }
        if (ImGui::SliderFloat("focus distance", &cameraFocusDistance, 0.1f, 100.0f)) {
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
    glm::dvec3 forward{
            glm::cos(cameraPitch) * glm::sin(cameraYaw),
            glm::sin(cameraPitch),
            -glm::cos(cameraPitch) * glm::cos(cameraYaw)
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
