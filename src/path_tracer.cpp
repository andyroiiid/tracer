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
    ys.resize(imageHeight);
    std::iota(ys.begin(), ys.end(), 0);
}

void PathTracer::sample(const Camera &camera, const World &world, int iteration) {
    double alpha = 1.0 / iteration;
    std::for_each(std::execution::par_unseq, ys.begin(), ys.end(), [&](int y) {
        for (int x = 0; x < imageWidth; x++) {
            double u = (x + randomDouble()) / (imageWidth - 1);
            double v = (y + randomDouble()) / (imageHeight - 1);
            glm::vec3 color = raytrace(camera.getRay(u, v), world, maxDepth);
            image.pixel(x, y) = glm::mix(image.pixel(x, y), color, alpha); // blend with previous samples
        }
    });
}

glm::vec3 PathTracer::raytrace(const Ray &ray, const World &world, int depth) {
    if (depth <= 0) return {0.0f, 0.0f, 0.0f};
    HitRecord hit = world.hit(ray, 0.0001, std::numeric_limits<double>::infinity());
    if (hit.hit) {
        ScatterResult scatter = hit.material->scatter(ray, hit);
        if (scatter.dropRay) {
            return {0.0f, 0.0f, 0.0f};
        } else {
            return scatter.attenuation * raytrace(scatter.scatteredRay, world, depth - 1);
        }
    }
    return world.traceSky(ray);
}
