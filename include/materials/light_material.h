//
// Created by andyroiiid on 7/19/21.
//

#ifndef TRACER_LIGHT_MATERIAL_H
#define TRACER_LIGHT_MATERIAL_H

#include "materials/material.h"

class LightMaterial : public Material {
public:
    explicit LightMaterial(const glm::vec3 &emissive) : emissive(emissive) {}

    [[nodiscard]] ScatterResult scatter(const Ray &ray, const HitRecord &hit) const override;

    [[nodiscard]] glm::vec3 emitted() const override;

private:
    glm::vec3 emissive;
};

#endif //TRACER_LIGHT_MATERIAL_H
