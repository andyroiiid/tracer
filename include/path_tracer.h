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
    PathTracer(int imageWidth, int imageHeight, int maxDepth);

    void sample(int iteration);

    [[nodiscard]] const Image &getImage() const { return image; }

private:
    glm::vec3 raytrace(const Ray &ray, int depth);

    const int imageWidth;
    const int imageHeight;
    const int maxDepth;

    Image image;
    Camera camera;
    const World world;

    // data for parallel execution
    std::vector<int> ys;
};

#endif //TRACER_PATH_TRACER_H
