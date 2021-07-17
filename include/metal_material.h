//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_METAL_MATERIAL_H
#define TRACER_METAL_MATERIAL_H

#include "material.h"

class MetalMaterial : public Material {
public:
    explicit MetalMaterial(const glm::vec3 &albedo, double roughness) : albedo(albedo), roughness(roughness) {}

    [[nodiscard]] ScatterResult scatter(const Ray &ray, const HitRecord &hit) const override;

private:
    glm::vec3 albedo;
    double roughness;
};

#endif //TRACER_METAL_MATERIAL_H
