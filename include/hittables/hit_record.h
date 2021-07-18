//
// Created by andyroiiid on 7/18/2021.
//

#ifndef TRACER_HIT_RECORD_H
#define TRACER_HIT_RECORD_H

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

#endif //TRACER_HIT_RECORD_H
