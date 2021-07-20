//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_INTERACTIVE_RENDERER_H
#define TRACER_INTERACTIVE_RENDERER_H

#include <memory>
#include <taskflow/core/executor.hpp>
#include <GLFW/glfw3.h>

#include "non_copyable.h"
#include "realtime/quad.h"
#include "realtime/texture.h"
#include "tracing/path_tracer.h"
#include "realtime/interactive_input.h"
#include "realtime/interactive_camera.h"

class InteractiveRenderer : NonCopyable {
public:
    explicit InteractiveRenderer(GLFWwindow *window) : input(window) {}

    void resizeWindow(int newWidth, int newHeight);

    inline void resetIteration() { nextIteration = 1; }

    void update(double deltaTime);

    void draw();

    void ui();

private:
    void recreateResources(int width, int height);

    Quad quad;

    bool resourcesDirty = true;

    int windowWidth = 1;
    int windowHeight = 1;
    int downScale = 8;
    int maxDepth = 16;

    std::unique_ptr<Texture> texture;
    std::unique_ptr<PathTracer> pathTracer;

    InteractiveInput input;
    InteractiveCamera camera;
    World world;

    tf::Executor executor;

    int nextIteration = 1;
    int iterationTarget = 64;

    tf::Future<void> renderFuture;
};

#endif //TRACER_INTERACTIVE_RENDERER_H
