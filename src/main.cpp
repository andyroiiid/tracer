#include "path_tracer.h"

int main() {
    constexpr int imageWidth = 1024;
    constexpr int imageHeight = 1024;

    PathTracer tracer(imageWidth, imageHeight, 32);

    for (int i = 1; i <= 32; i++) {
        tracer.sample(i);
        printf("finished sample pass %d\n", i);
    }

    tracer.getImage().writeFile("test.png");

//    // gamma correction
//    Image image = tracer.getImage();
//    for (int y = 0; y < imageHeight; y++) {
//        for (int x = 0; x < imageWidth; x++) {
//            image.pixel(x, y) = glm::sqrt(image.pixel(x, y));
//        }
//    }
//    image.writeFile("test.png");

    return 0;
}
