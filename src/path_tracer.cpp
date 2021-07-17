//
// Created by andyroiiid on 7/17/2021.
//

#include "path_tracer.h"

#include <execution>

#include "material.h"

PathTracer::PathTracer(int imageWidth, int imageHeight, int maxDepth)
        : imageWidth(imageWidth),
          imageHeight(imageHeight),
          maxDepth(maxDepth),
          image(imageWidth, imageHeight) {
    constexpr glm::dvec3 position{2.0, 2.0, 2.0};
    constexpr glm::dvec3 target{0.0, 0.0, 0.0};
    constexpr glm::dvec3 up{0.0, 1.0, 0.0};
    camera = Camera(
            position, target, up,
            45.0,
            double(imageWidth) / double(imageHeight),
            0.2,
            glm::length(target - position)
    );

    ys.resize(imageHeight);
    std::iota(ys.begin(), ys.end(), 0);
}

void PathTracer::sample(int iteration) {
    double alpha = 1.0 / iteration;
    std::for_each(std::execution::par_unseq, ys.begin(), ys.end(), [&](int y) {
        for (int x = 0; x < imageWidth; x++) {
            double u = (x + randomDouble()) / (imageWidth - 1);
            double v = (y + randomDouble()) / (imageHeight - 1);
            glm::dvec3 color = raytrace(camera.getRay(u, v), maxDepth);
            image.pixel(x, y) = glm::mix(image.pixel(x, y), color, alpha); // blend with previous samples
        }
    });
}

glm::dvec3 PathTracer::raytrace(const Ray &ray, int depth) {
    if (depth <= 0) return {0.0, 0.0, 0.0};
    HitRecord hit = world.hit(ray, 0.0001, std::numeric_limits<double>::infinity());
    if (hit.hit) {
        ScatterResult scatter = hit.material->scatter(ray, hit);
        if (scatter.dropRay) {
            return {0.0, 0.0, 0.0};
        } else {
            return scatter.attenuation * raytrace(scatter.scatteredRay, depth - 1);
        }
    }
    return world.traceSky(ray);
}
