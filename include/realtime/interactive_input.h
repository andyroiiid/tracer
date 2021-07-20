//
// Created by andyroiiid on 7/21/2021.
//

#ifndef TRACER_INTERACTIVE_INPUT_H
#define TRACER_INTERACTIVE_INPUT_H

#include <GLFW/glfw3.h>

class InteractiveInput {
public:
    explicit InteractiveInput(GLFWwindow *window) : window(window) {}

    double axisForward();

    double axisRight();

    double axisUp();

    [[nodiscard]] double axisTurn() const;

    [[nodiscard]] double axisLookUp() const;

    bool update();

private:
    GLFWwindow *window;

    bool moving = false;

    bool prevRightPressed = false;

    double prevXPos = 0.0;
    double prevYPos = 0.0;
    double currXPos = 0.0;
    double currYPos = 0.0;
};

#endif //TRACER_INTERACTIVE_INPUT_H
