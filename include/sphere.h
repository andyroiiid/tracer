//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_SPHERE_H
#define TRACER_SPHERE_H

#include "hittable.h"
#include "material.h"

class Sphere : public Hittable {
public:
    Sphere(const glm::dvec3 &center, double radius, std::shared_ptr<Material> material)
            : center(center), radius(radius), material(std::move(material)) {}

    [[nodiscard]] HitRecord hit(const Ray &ray, double tMin, double tMax) const override;

private:
    glm::dvec3 center;
    double radius;
    std::shared_ptr<Material> material;
};

#endif //TRACER_SPHERE_H
