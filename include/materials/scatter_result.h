//
// Created by andyroiiid on 7/18/2021.
//

#ifndef TRACER_SCATTER_RESULT_H
#define TRACER_SCATTER_RESULT_H

#include "tracing/ray.h"

struct ScatterResult {
    bool dropRay;
    glm::vec3 attenuation;
    Ray scatteredRay;
};

#endif //TRACER_SCATTER_RESULT_H
