//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_RAY_H
#define TRACER_RAY_H

struct Ray {
    [[nodiscard]] glm::dvec3 at(double t) const {
        return origin + t * direction;
    }

    glm::dvec3 origin;
    glm::dvec3 direction;
};

#endif //TRACER_RAY_H
