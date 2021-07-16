//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_CAMERA_H
#define TRACER_CAMERA_H

#include "ray.h"
#include "random.h"

class Camera {
public:
    Camera(
            const glm::dvec3 &lookFrom,
            const glm::dvec3 &lookAt,
            const glm::dvec3 &up,
            double vFoVDegrees,
            double aspectRatio,
            double aperture,
            double focusDistance
    ) {
        double viewportHeight = 2.0 * glm::tan(glm::radians(vFoVDegrees) / 2.0);
        double viewportWidth = aspectRatio * viewportHeight;

        glm::dvec3 w = glm::normalize(lookFrom - lookAt);
        glm::dvec3 u = glm::normalize(glm::cross(up, w));
        glm::dvec3 v = glm::cross(w, u);

        origin = lookFrom;
        horizontal = focusDistance * viewportWidth * u;
        vertical = focusDistance * viewportHeight * v;
        lowerLeftCorner = origin - horizontal * 0.5 - vertical * 0.5 - focusDistance * w;
        lensRadius = aperture / 2.0;
    }

    [[nodiscard]] Ray getRay(double u, double v) const {
        glm::dvec2 random = lensRadius * randomInCircle();
        glm::dvec3 newOrigin = origin + u * random.x + u * random.y;
        return {newOrigin, lowerLeftCorner + u * horizontal + v * vertical - newOrigin};
    }

private:
    glm::dvec3 origin{};
    glm::dvec3 horizontal{};
    glm::dvec3 vertical{};
    glm::dvec3 lowerLeftCorner{};
    double lensRadius = 0.0;
};

#endif //TRACER_CAMERA_H