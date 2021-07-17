//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_IMGUI_FUNCS_H
#define TRACER_IMGUI_FUNCS_H

#include <GLFW/glfw3.h>
#include <imgui.h>

void ImGui_Init(GLFWwindow *window);

void ImGui_Destroy();

void ImGui_NewFrame();

void ImGui_Render();

#endif //TRACER_IMGUI_FUNCS_H
