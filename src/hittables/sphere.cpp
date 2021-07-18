//
// Created by andyroiiid on 7/16/2021.
//

#include "hittables/sphere.h"

HitRecord Sphere::hit(const Ray &ray, double tMin, double tMax) const {
    glm::dvec3 oc = ray.origin - center;
    double a = glm::dot(ray.direction, ray.direction);
    double h = glm::dot(oc, ray.direction);
    double c = glm::dot(oc, oc) - radius * radius;

    double discriminant = h * h - a * c;
    if (discriminant < 0.0) {
        return HitRecord();
    }

    double sqrtDiscriminant = glm::sqrt(discriminant);
    double root = (-h - sqrtDiscriminant) / a;
    if (root < tMin || tMax < root) {
        root = (-h + sqrtDiscriminant) / a;
        if (root < tMin || tMax < root) {
            return HitRecord();
        }
    }

    glm::dvec3 normal = (ray.at(root) - center) / radius;
    return HitRecord(true, root, ray, normal, material);
}
