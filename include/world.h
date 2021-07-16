//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_WORLD_H
#define TRACER_WORLD_H

#include "hittable_list.h"

class World : public HittableList {
public:
    World();

    [[nodiscard]] inline glm::dvec3 traceSky(const Ray &ray) const {
        const glm::dvec3 direction = glm::normalize(ray.direction);
        return glm::mix(groundColor, skyColor, direction.y * 0.5 + 0.5);
    }

private:
    const glm::dvec3 groundColor{1.0};
    const glm::dvec3 skyColor{0.5, 0.7, 1.0};
};

#endif //TRACER_WORLD_H
