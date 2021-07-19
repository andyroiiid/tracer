//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_MATERIAL_H
#define TRACER_MATERIAL_H

#include "materials/scatter_result.h"

struct HitRecord;

struct Material {
    [[nodiscard]] virtual ScatterResult scatter(const Ray &ray, const HitRecord &hit) const = 0;

    [[nodiscard]] virtual glm::vec3 emitted() const { return {0.0f, 0.0f, 0.0f}; }
};

#endif //TRACER_MATERIAL_H
