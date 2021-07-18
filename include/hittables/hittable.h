//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_HITTABLE_H
#define TRACER_HITTABLE_H

#include "tracing/ray.h"

#include <memory>

struct Material;

struct HitRecord {
    HitRecord() = default; // no hit

    HitRecord(bool hit, double t, const Ray &ray, const glm::dvec3 &outwardNormal, std::shared_ptr<Material> material)
            : hit(hit),
              t(t),
              point(ray.at(t)),
              frontFace(glm::dot(ray.direction, outwardNormal) < 0.0),
              normal(frontFace ? outwardNormal : -outwardNormal),
              material(std::move(material)) {}

    bool hit = false;
    double t = 0.0;
    glm::dvec3 point{};
    bool frontFace = false;
    glm::dvec3 normal{};
    std::shared_ptr<Material> material = nullptr;
};

struct Hittable {
    [[nodiscard]] virtual HitRecord hit(const Ray &ray, double tMin, double tMax) const = 0;
};

#endif //TRACER_HITTABLE_H
