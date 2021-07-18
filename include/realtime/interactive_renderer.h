//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_INTERACTIVE_RENDERER_H
#define TRACER_INTERACTIVE_RENDERER_H

#include <memory>
#include <taskflow/core/executor.hpp>

#include "non_copyable.h"
#include "realtime/quad.h"
#include "realtime/texture.h"
#include "tracing/path_tracer.h"

class InteractiveRenderer : NonCopyable {
public:
    void resizeWindow(int newWidth, int newHeight);

    inline void resetIteration() { nextIteration = 1; }

    void update();

    void draw();

    void ui();

private:
    void recreateResources(int width, int height);

    void recreateCamera();

    Quad quad;

    bool resourcesDirty = true;

    int windowWidth = 1;
    int windowHeight = 1;
    int downScale = 4;
    int maxDepth = 32;

    bool cameraDirty = true;

    glm::vec3 cameraPosition{2.0f, 2.0f, 2.0f};
    float cameraFoV = glm::radians(45.0f);
    float cameraAperture = 0.1f;
    float cameraFocusDistance = 3.0f;

    std::unique_ptr<Texture> texture;
    std::unique_ptr<PathTracer> pathTracer;

    Camera camera;
    World world;

    tf::Executor executor;

    int nextIteration = 1;
    int iterationTarget = 64;

    tf::Future<void> renderFuture;
};

#endif //TRACER_INTERACTIVE_RENDERER_H
