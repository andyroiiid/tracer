//
// Created by andyroiiid on 7/16/2021.
//

#include "glass_material.h"

#include "hittable.h"
#include "random.h"

ScatterResult GlassMaterial::scatter(const Ray &ray, const HitRecord &hit) const {
    double refractionRatio = hit.frontFace ? 1.0 / ior : ior;
    glm::dvec3 unitDirection = glm::normalize(ray.direction);

    double cosTheta = glm::min(glm::dot(-unitDirection, hit.normal), 1.0);
    double sinTheta = glm::sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0 || reflectance(cosTheta, refractionRatio) > randomDouble();

    glm::dvec3 refractionDirection =
            cannotRefract ?
            glm::reflect(unitDirection, hit.normal) :
            glm::refract(unitDirection, hit.normal, refractionRatio);

    Ray refractedRay{hit.point, refractionDirection};
    return {false, {1.0f, 1.0f, 1.0f}, refractedRay};
}

double GlassMaterial::reflectance(double cosine, double refractionRatio) {
    double r0 = (1.0 - refractionRatio) / (1.0 + refractionRatio);
    r0 *= r0;
    return r0 + (1.0 - r0) * glm::pow(1.0 - cosine, 5.0);
}
