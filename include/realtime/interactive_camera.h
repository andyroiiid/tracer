//
// Created by andyroiiid on 7/21/2021.
//

#ifndef TRACER_INTERACTIVE_CAMERA_H
#define TRACER_INTERACTIVE_CAMERA_H

#include "tracing/camera.h"

class InteractiveCamera {
public:
    inline void markDirty() { dirty = true; }

    bool checkRecreate(int windowWidth, int windowHeight);

    void ui();

    [[nodiscard]] const Camera &getCamera() const { return camera; }

    [[nodiscard]] glm::dvec3 forward() const { return {glm::sin(yaw), 0.0, -glm::cos(yaw)}; }

    [[nodiscard]] glm::dvec3 right() const { return {glm::cos(yaw), 0.0, glm::sin(yaw)}; }

    inline void move(const glm::dvec3 &deltaPosition) {
        position += deltaPosition;
        markDirty();
    }

    inline void rotateYaw(double deltaYaw) {
        yaw = yaw + deltaYaw;
        constexpr auto two_pi = glm::two_pi<double>();
        if (yaw > two_pi) {
            yaw -= two_pi;
        } else if (yaw < 0.0) {
            yaw += two_pi;
        }
        markDirty();
    }

    inline void rotatePitch(double deltaPitch) {
        pitch = glm::clamp(pitch + deltaPitch, glm::radians(-89.9), glm::radians(89.9));
        markDirty();
    }

private:
    bool dirty = true;

    glm::dvec3 position{0.0, 16.0, 16.0};
    double yaw = glm::pi<double>();
    double pitch = glm::radians(50.0);

    float fov = glm::radians(45.0f);
    float aperture = 0.1f;
    float focusDistance = 24.0f;

    Camera camera;
};

#endif //TRACER_INTERACTIVE_CAMERA_H
