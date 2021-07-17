//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_PATH_TRACER_H
#define TRACER_PATH_TRACER_H

#include "image.h"
#include "camera.h"
#include "world.h"

class PathTracer {
public:
    PathTracer(int imageWidth, int imageHeight);

    void sample(const Camera &camera, const World &world, int iteration, int maxDepth);

    [[nodiscard]] inline const Image &getImage() const { return image; }

private:
    glm::vec3 raytrace(const Ray &ray, const World &world, int depth);

    const int imageWidth;
    const int imageHeight;

    Image image;

    // data for parallel execution
    std::vector<int> ys;
};

#endif //TRACER_PATH_TRACER_H
