#include <GLFW/glfw3.h>

#include "interactive_renderer.h"

void renderLoop(GLFWwindow *window) {
    double downScale = 3.0;

    int prevWidth = -1, prevHeight = -1;
    InteractiveRenderer renderer;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int currWidth, currHeight;
        glfwGetFramebufferSize(window, &currWidth, &currHeight);

        if (currWidth != prevWidth || currHeight != prevHeight) {
            renderer.resize(int(currWidth / downScale), int(currHeight / downScale));
            prevWidth = currWidth;
            prevHeight = currHeight;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            renderer.clearSamples();
        }

        renderer.updateSamples(64);

        glViewport(0, 0, currWidth, currHeight);

        glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
        glClear((GL_COLOR_BUFFER_BIT));

        renderer.draw();

        glfwSwapBuffers(window);
    }
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "tracer", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    renderLoop(window);
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
