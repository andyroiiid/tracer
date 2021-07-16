#include <cstdio>
#include <execution>

#include "image.h"
#include "camera.h"
#include "random.h"
#include "material.h"
#include "world.h"

glm::dvec3 raytrace(const Ray &ray, const World &world, int depth) {
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
    return world.traceSky(ray);
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

    const World world;

    Image image(imageWidth, imageHeight);

    // data for parallel execution
    std::vector<int> ys(imageHeight);
    std::iota(ys.begin(), ys.end(), 0);

    for (int i = 1; i <= samples; i++) {
        const double alpha = 1.0 / i;

        std::for_each(std::execution::par_unseq, ys.begin(), ys.end(), [&](int y) {
            for (int x = 0; x < imageWidth; x++) {
                double u = (x + randomDouble()) / (imageWidth - 1);
                double v = (y + randomDouble()) / (imageHeight - 1);
                glm::dvec3 color = raytrace(camera.getRay(u, v), world, maxDepth);
                image.pixel(x, y) = glm::mix(image.pixel(x, y), color, alpha); // blend with previous samples
            }
        });

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
