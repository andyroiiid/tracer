//
// Created by andyroiiid on 7/21/2021.
//

#include "realtime/interactive_input.h"

double InteractiveInput::axisForward() {
    double value = 0.0;
    if (glfwGetKey(window, GLFW_KEY_W)) value += 1.0;
    if (glfwGetKey(window, GLFW_KEY_S)) value -= 1.0;
    return value;
}

double InteractiveInput::axisRight() {
    double value = 0.0;
    if (glfwGetKey(window, GLFW_KEY_D)) value += 1.0;
    if (glfwGetKey(window, GLFW_KEY_A)) value -= 1.0;
    return value;
}

double InteractiveInput::axisUp() {
    double value = 0.0;
    if (glfwGetKey(window, GLFW_KEY_E)) value += 1.0;
    if (glfwGetKey(window, GLFW_KEY_Q)) value -= 1.0;
    return value;
}

double InteractiveInput::axisTurn() const {
    return (currXPos - prevXPos) * 0.002;
}

double InteractiveInput::axisLookUp() const {
    return (currYPos - prevYPos) * 0.002;
}

bool InteractiveInput::update() {
    prevXPos = currXPos;
    prevYPos = currYPos;
    glfwGetCursorPos(window, &currXPos, &currYPos);

    bool currRightPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (currRightPressed && !prevRightPressed) {
        moving = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else if (!currRightPressed && prevRightPressed) {
        moving = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    prevRightPressed = currRightPressed;

    return moving;
}
