//
// Created by andyroiiid on 7/16/2021.
//

#ifndef TRACER_IMAGE_H
#define TRACER_IMAGE_H

#include <vector>
#include <string>

#include <glm/vec3.hpp>

class Image {
public:
    Image(int width, int height)
            : width(width),
              height(height),
              pixels(width * height) {}

    glm::dvec3 &pixel(int x, int y) {
        return pixels[x + y * width];
    }

    void writeFile(const std::string &filename) const;

    static glm::u8vec3 convertColor(const glm::dvec3 &color);

private:
    int width = 0;
    int height = 0;
    std::vector<glm::dvec3> pixels;
};

#endif //TRACER_IMAGE_H