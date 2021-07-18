//
// Created by andyroiiid on 7/16/2021.
//

#include "materials/metal_material.h"

#include "hittables/hittable.h"
#include "random.h"

ScatterResult MetalMaterial::scatter(const Ray &ray, const HitRecord &hit) const {
    glm::dvec3 scatterDirection = glm::reflect(ray.direction, hit.normal);
    Ray scatteredRay{hit.point, scatterDirection + roughness * randomInSphere()};
    return {glm::dot(scatterDirection, hit.normal) < 0.0, albedo, scatteredRay};
}
