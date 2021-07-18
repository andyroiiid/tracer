//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_PATH_TRACER_H
#define TRACER_PATH_TRACER_H

#include <taskflow/core/executor.hpp>

#include "image.h"
#include "tracing/camera.h"
#include "tracing/world.h"

class PathTracer {
public:
    PathTracer(tf::Executor &executor, int imageWidth, int imageHeight);

    void sample(const Camera &camera, const World &world, int iteration, int maxDepth);

    [[nodiscard]] inline const Image &getImage() const { return image; }

private:
    glm::vec3 raytrace(const Ray &ray, const World &world, int depth);

    tf::Executor &executor;

    const int imageWidth;
    const int imageHeight;
    Image image;
};

#endif //TRACER_PATH_TRACER_H
