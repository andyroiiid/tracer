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

    inline glm::vec3 &pixel(int x, int y) {
        return pixels[x + y * width];
    }

    [[nodiscard]] inline const float *data() const {
        return &pixels.data()->x;
    }

    void writeFile(const std::string &filename) const;

    static glm::vec3 ACESToneMapping(const glm::vec3 &color);

    static glm::u8vec3 convertColor(const glm::vec3 &color);

private:
    int width = 0;
    int height = 0;
    std::vector<glm::vec3> pixels;
};

#endif //TRACER_IMAGE_H
