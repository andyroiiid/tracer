//
// Created by andyroiiid on 7/16/2021.
//

#include "image.h"

#include <algorithm>
#include <iterator>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>

void Image::writeFile(const std::string &filename) const {
    std::vector<glm::u8vec3> data;
    std::transform(pixels.begin(), pixels.end(), std::back_inserter(data), convertColor);

    stbi_flip_vertically_on_write(true);
    stbi_write_png(filename.c_str(), width, height, 3, data.data(), width * 3);
}

glm::vec3 Image::ACESToneMapping(const glm::vec3 &color) {
    const float A = 2.51f;
    const float B = 0.03f;
    const float C = 2.43f;
    const float D = 0.59f;
    const float E = 0.14f;
    return (color * (A * color + B)) / (color * (C * color + D) + E);
}

glm::u8vec3 Image::convertColor(const glm::vec3 &color) {
    return ACESToneMapping(color) * 255.0f;
}
