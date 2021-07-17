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

glm::u8vec3 Image::convertColor(const glm::vec3 &color) {
    return color * 255.0f;
}
