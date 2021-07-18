//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_HITTABLE_H
#define TRACER_HITTABLE_H

#include "hittables/hit_record.h"

struct Hittable {
    [[nodiscard]] virtual HitRecord hit(const Ray &ray, double tMin, double tMax) const = 0;
};

#endif //TRACER_HITTABLE_H
