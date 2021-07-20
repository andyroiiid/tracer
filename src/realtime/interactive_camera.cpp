//
// Created by andyroiiid on 7/21/2021.
//

#include "realtime/interactive_camera.h"

#include <imgui.h>

bool InteractiveCamera::checkRecreate(int windowWidth, int windowHeight) {
    if (!dirty) return false;

    glm::dvec3 forward{
            glm::cos(pitch) * glm::sin(yaw),
            glm::sin(pitch),
            -glm::cos(pitch) * glm::cos(yaw)
    };

    constexpr glm::dvec3 up{0.0, 1.0, 0.0};

    camera = Camera(
            position, forward, up,
            fov,
            double(windowWidth) / double(windowHeight),
            aperture,
            focusDistance
    );

    dirty = false;

    return true;
}

void InteractiveCamera::ui() {
    if (ImGui::CollapsingHeader("camera")) {
        ImGui::LabelText("position", "%.2f, %.2f, %.2f", position.x, position.y, position.z);
        ImGui::LabelText("yaw", "%f", glm::degrees(yaw));
        ImGui::LabelText("pitch", "%f", glm::degrees(pitch));

        if (ImGui::SliderAngle("fov", &fov, 1.0f, 179.0f)) {
            markDirty();
        }
        if (ImGui::SliderFloat("aperture", &aperture, 0.0f, 1.0f)) {
            markDirty();
        }
        if (ImGui::SliderFloat("focus distance", &focusDistance, 0.1f, 100.0f)) {
            markDirty();
        }
    }
}
