//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_WORLD_H
#define TRACER_WORLD_H

#include "hittables/hittable_list.h"

class World : public HittableList {
public:
    World();

    bool ui();

    [[nodiscard]] inline glm::vec3 traceSky(const Ray &ray) const {
        const glm::dvec3 direction = glm::normalize(ray.direction);
        return glm::mix(groundColor, skyColor, direction.y * 0.5 + 0.5);
    }

private:
    glm::vec3 groundColor{1.0f};
    glm::vec3 skyColor{0.5f, 0.7f, 1.0f};
};

#endif //TRACER_WORLD_H
