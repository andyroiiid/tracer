//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_WORLD_H
#define TRACER_WORLD_H

#include "hittables/hittable_list.h"

class World {
public:
    World();

    bool ui();

    [[nodiscard]] inline HitRecord hit(const Ray &ray, double tMin, double tMax) const {
        return objects.hit(ray, tMin, tMax);
    }

    [[nodiscard]] inline glm::vec3 traceSky(const Ray &ray) const {
        return skyColor;
    }

private:
    HittableList objects;

    glm::vec3 skyColor{0.5f, 0.7f, 1.0f};
};

#endif //TRACER_WORLD_H
