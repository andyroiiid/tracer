#include "realtime/interactive_renderer.h"
#include "realtime/imgui_funcs.h"

void renderLoop(GLFWwindow *window) {
    int prevWidth = -1, prevHeight = -1;
    InteractiveRenderer renderer;

    bool prevRightPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    double prevTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int currWidth, currHeight;
        glfwGetFramebufferSize(window, &currWidth, &currHeight);
        if (currWidth != prevWidth || currHeight != prevHeight) {
            renderer.resizeWindow(currWidth, currHeight);
            prevWidth = currWidth;
            prevHeight = currHeight;
        }

        bool currRightPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
        if (currRightPressed && !prevRightPressed) {
            renderer.startMoving(window);
        } else if (!currRightPressed && prevRightPressed) {
            renderer.stopMoving(window);
        }
        prevRightPressed = currRightPressed;

        double currTime = glfwGetTime();
        renderer.update(currTime - prevTime, window);
        prevTime = currTime;

        glViewport(0, 0, currWidth, currHeight);

        glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
        glClear((GL_COLOR_BUFFER_BIT));

        renderer.draw();

        ImGui_NewFrame();
        renderer.ui();
        ImGui_Render();

        glfwSwapBuffers(window);
    }
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "tracer", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    ImGui_Init(window);

    renderLoop(window);

    ImGui_Destroy();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
