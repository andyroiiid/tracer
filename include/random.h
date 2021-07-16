//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_RANDOM_H
#define TRACER_RANDOM_H

#include <glm/gtc/constants.hpp>

double randomDouble();

static inline glm::dvec2 randomOnCircle() {
    double theta = glm::two_pi<double>() * randomDouble();
    return {glm::cos(theta), glm::sin(theta)};
}

static inline glm::dvec2 randomInCircle() {
    double r = glm::sqrt(randomDouble());
    return randomOnCircle() * r;
}

static inline glm::dvec3 randomOnSphere() {
    double theta = glm::two_pi<double>() * randomDouble();
    double phi = glm::acos(2.0 * randomDouble() - 1.0);
    return {
            glm::sin(phi) * glm::cos(theta),
            glm::sin(phi) * glm::sin(theta),
            glm::cos(phi)
    };
}

static inline glm::dvec3 randomInSphere() {
    double r = std::cbrt(randomDouble());
    return randomOnSphere() * r;
}

static inline glm::dvec3 randomInHemisphere(const glm::dvec3 &normal) {
    glm::dvec3 v = randomInSphere();
    return glm::sign(glm::dot(v, normal)) * v;
}

#endif //TRACER_RANDOM_H
