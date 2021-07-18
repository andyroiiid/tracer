//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_MATERIAL_H
#define TRACER_MATERIAL_H

#include "tracing/ray.h"

struct HitRecord;

struct ScatterResult {
    bool dropRay;
    glm::vec3 attenuation;
    Ray scatteredRay;
};

struct Material {
    [[nodiscard]] virtual ScatterResult scatter(const Ray &ray, const HitRecord &hit) const = 0;
};

#endif //TRACER_MATERIAL_H
