//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_HITTABLE_LIST_H
#define TRACER_HITTABLE_LIST_H

#include <vector>
#include <memory>

#include "hittable.h"

class HittableList : public Hittable {
public:
    void add(const std::shared_ptr<Hittable> &object) {
        objects.push_back(object);
    }

    [[nodiscard]] HitRecord hit(const Ray &ray, double tMin, double tMax) const override {
        HitRecord hitAnything{};
        double closestSoFar = tMax;
        for (const auto &object : objects) {
            HitRecord hit = object->hit(ray, tMin, closestSoFar);
            if (hit.hit) {
                hitAnything = hit;
                closestSoFar = hit.t;
            }
        }
        return hitAnything;
    }

private:
    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif //TRACER_HITTABLE_LIST_H
