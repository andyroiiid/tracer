//
// Created by andyroiiid on 7/19/21.
//

#include "materials/light_material.h"

ScatterResult LightMaterial::scatter(const Ray &ray, const HitRecord &hit) const {
    return {true};
}

glm::vec3 LightMaterial::emitted() const {
    return emissive;
}
