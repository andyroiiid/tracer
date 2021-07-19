//
// Created by andyroiiid on 7/17/2021.
//

#include "tracing/path_tracer.h"

#include <taskflow/core/algorithm/for_each.hpp>

#include "materials/material.h"

PathTracer::PathTracer(tf::Executor &executor, int imageWidth, int imageHeight)
        : executor(executor),
          imageWidth(imageWidth),
          imageHeight(imageHeight),
          image(imageWidth, imageHeight) {
}

void PathTracer::sample(const Camera &camera, const World &world, int iteration, int maxDepth) {
    double alpha = 1.0 / iteration;
    tf::Taskflow taskflow;
    taskflow.for_each_index(0, imageHeight, 1, [&](int y) {
        for (int x = 0; x < imageWidth; x++) {
            double u = (x + randomDouble()) / (imageWidth - 1);
            double v = (y + randomDouble()) / (imageHeight - 1);
            glm::vec3 color = raytrace(camera.getRay(u, v), world, maxDepth);
            image.pixel(x, y) = glm::mix(image.pixel(x, y), color, alpha); // blend with previous samples
        }
    });
    executor.run(taskflow).get();
}

glm::vec3 PathTracer::raytrace(const Ray &ray, const World &world, int depth) {
    if (depth <= 0) return {0.0f, 0.0f, 0.0f};
    HitRecord hit = world.hit(ray, 0.0001, std::numeric_limits<double>::infinity());
    if (hit.hit) {
        ScatterResult scatter = hit.material->scatter(ray, hit);
        glm::vec3 color = hit.material->emitted();
        if (!scatter.dropRay) {
            color += scatter.attenuation * raytrace(scatter.scatteredRay, world, depth - 1);
        }
        return color;
    }
    return world.traceSky(ray);
}
