//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_INTERACTIVE_RENDERER_H
#define TRACER_INTERACTIVE_RENDERER_H

#include <memory>

#include "non_copyable.h"
#include "quad.h"
#include "texture.h"
#include "path_tracer.h"

class InteractiveRenderer : NonCopyable {
public:
    void resize(int width, int height);

    inline void clearSamples() { iteration = 1; }

    void updateSamples(int iterationTarget);

    void draw();

private:
    Quad quad;
    std::unique_ptr<Texture> texture;
    std::unique_ptr<PathTracer> pathTracer;

    Camera camera;
    World world;

    int iteration = 1;
};

#endif //TRACER_INTERACTIVE_RENDERER_H
