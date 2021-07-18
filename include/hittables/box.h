//
// Created by andyroiiid on 7/18/2021.
//

#ifndef TRACER_BOX_H
#define TRACER_BOX_H

#include "hittables/hittable_list.h"
#include "materials/material.h"

class Box : public HittableList {
public:
    Box(const glm::dvec3 &p0, const glm::dvec3 &p1, const std::shared_ptr<Material> &material);
};

#endif //TRACER_BOX_H
