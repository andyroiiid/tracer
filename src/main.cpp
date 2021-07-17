#include <GLFW/glfw3.h>

#include "quad.h"
#include "texture.h"
#include "path_tracer.h"

void renderLoop(GLFWwindow *window) {
    constexpr int imageWidth = 640;
    constexpr int imageHeight = 360;

    Quad quad;
    Texture texture(imageWidth, imageHeight);

    constexpr glm::dvec3 position{2.0, 2.0, 2.0};
    constexpr glm::dvec3 target{0.0, 0.0, 0.0};
    constexpr glm::dvec3 up{0.0, 1.0, 0.0};
    Camera camera(
            position, target, up,
            45.0,
            double(imageWidth) / double(imageHeight),
            0.2,
            glm::length(target - position)
    );

    World world;

    PathTracer tracer(imageWidth, imageHeight, 32);

    int iteration = 1;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            iteration = 1;
        }

        if (iteration <= 256) {
            tracer.sample(camera, world, iteration);
            texture.upload(tracer.getImage().data());
            glfwSetWindowTitle(window, ("iteration: " + std::to_string(iteration)).c_str());
            iteration++;
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
        glClear((GL_COLOR_BUFFER_BIT));

        texture.bind(0);
        quad.draw();
        glBindTextureUnit(0, 0);

        glfwSwapBuffers(window);
    }
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(1280, 720, "tracer", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    renderLoop(window);
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
