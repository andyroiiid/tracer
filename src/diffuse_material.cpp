//
// Created by andyroiiid on 7/16/2021.
//

#include "diffuse_material.h"

#include "hittable.h"
#include "random.h"

ScatterResult DiffuseMaterial::scatter(const Ray &ray, const HitRecord &hit) const {
    Ray scatteredRay{hit.point, randomInHemisphere(hit.normal)};
    return {false, albedo, scatteredRay};
}
