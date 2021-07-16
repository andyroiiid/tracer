//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_DIFFUSE_MATERIAL_H
#define TRACER_DIFFUSE_MATERIAL_H

#include "material.h"

class DiffuseMaterial : public Material {
public:
    explicit DiffuseMaterial(const glm::dvec3 &albedo) : albedo(albedo) {}

    [[nodiscard]] ScatterResult scatter(const Ray &ray, const HitRecord &hit) const override;

private:
    glm::dvec3 albedo;
};

#endif //TRACER_DIFFUSE_MATERIAL_H
