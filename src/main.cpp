#include <cstdio>

#include "image.h"
#include "camera.h"
#include "random.h"
#include "material.h"
#include "world.h"

glm::dvec3 skyColor(const Ray &ray) {
    const glm::dvec3 direction = glm::normalize(ray.direction);
    constexpr glm::dvec3 groundColor{1.0};
    constexpr glm::dvec3 skyColor{0.5, 0.7, 1.0};
    return glm::mix(groundColor, skyColor, direction.y * 0.5 + 0.5);
}

glm::dvec3 raytrace(const Ray &ray, const Hittable &world, int depth) {
    if (depth <= 0) return {0.0, 0.0, 0.0};
    HitRecord hit = world.hit(ray, 0.0001, std::numeric_limits<double>::infinity());
    if (hit.hit) {
        ScatterResult scatter = hit.material->scatter(ray, hit);
        if (scatter.dropRay) {
            return {0.0, 0.0, 0.0};
        } else {
            return scatter.attenuation * raytrace(scatter.scatteredRay, world, depth - 1);
        }
    }
    return skyColor(ray);
}

int main() {
    constexpr int imageWidth = 512;
    constexpr int imageHeight = 512;
    constexpr int samples = 64;
    constexpr int maxDepth = 32;

    constexpr glm::dvec3 position{2.0, 2.0, 2.0};
    constexpr glm::dvec3 target{0.0, 0.0, 0.0};
    constexpr glm::dvec3 up{0.0, 1.0, 0.0};
    const Camera camera(
            position, target, up,
            45.0,
            double(imageWidth) / double(imageHeight),
            0.2,
            glm::length(target - position)
    );

    World world;

    Image image(imageWidth, imageHeight);

    for (int i = 1; i <= samples; i++) {
        double alpha = 1.0 / i;
        for (int y = 0; y < imageHeight; y++) {
            for (int x = 0; x < imageWidth; x++) {
                double u = (x + randomDouble()) / (imageWidth - 1);
                double v = (y + randomDouble()) / (imageHeight - 1);
                glm::dvec3 color = raytrace(camera.getRay(u, v), world, maxDepth);
                image.pixel(x, y) = glm::mix(image.pixel(x, y), color, alpha); // blend with previous samples
            }
        }
        printf("finished sample pass %d\n", i);
    }

    // gamma correction
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            image.pixel(x, y) = glm::sqrt(image.pixel(x, y));
        }
    }

    image.writeFile("test.png");

    return 0;
}
