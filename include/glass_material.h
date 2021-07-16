//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_GLASS_MATERIAL_H
#define TRACER_GLASS_MATERIAL_H

#include "material.h"

class GlassMaterial : public Material {
public:
    explicit GlassMaterial(double ior) : ior(ior) {}

    [[nodiscard]] ScatterResult scatter(const Ray &ray, const HitRecord &hit) const override;

private:
    static double reflectance(double cosine, double refractionRatio);

    double ior;
};

#endif //TRACER_GLASS_MATERIAL_H
