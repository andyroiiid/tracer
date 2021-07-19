//
// Created by andyroiiid on 7/16/2021.
//

#include "tracing/world.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "hittables/box.h"
#include "hittables/rect.h"
#include "hittables/sphere.h"
#include "materials/diffuse_material.h"
#include "materials/metal_material.h"
#include "materials/glass_material.h"
#include "materials/light_material.h"

World::World() {
    std::shared_ptr<Material> ground = std::make_shared<DiffuseMaterial>(glm::vec3{0.5f, 0.5f, 0.5f});
    objects.add(std::make_shared<XZRect>(-10.0, -10.0, 10.0, 10.0, 0.0, true, ground));

    std::shared_ptr<Material> glass = std::make_shared<GlassMaterial>(1.5);
    objects.add(std::make_shared<Box>(glm::dvec3{-1.0, 0.0, -1.0}, glm::dvec3{1.0, 2.0, 1.0}, glass));
    objects.add(std::make_shared<Sphere>(glm::dvec3{0.0, 1.0, 0.0}, -0.9, glass));

    std::shared_ptr<Material> blue = std::make_shared<DiffuseMaterial>(glm::vec3{0.4f, 0.8f, 1.0f});
    objects.add(std::make_shared<Sphere>(glm::dvec3{-2.0, 1.0, 2.0}, 1.0, blue));

    std::shared_ptr<Material> light = std::make_shared<LightMaterial>(glm::vec3{2.0f, 2.0f, 2.0f});
    objects.add(std::make_shared<Sphere>(glm::dvec3{-2.0, 1.0, 0.0}, 1.0, light));

    std::shared_ptr<Material> metal = std::make_shared<MetalMaterial>(glm::vec3{0.7f, 0.6f, 0.5f}, 0.0);
    objects.add(std::make_shared<Sphere>(glm::dvec3{2.0, 1.0, 0.0}, 1.0, metal));
}

bool World::ui() {
    bool dirty = false;

    if (ImGui::ColorEdit3("sky color", glm::value_ptr(skyColor))) {
        dirty = true;
    }

    return dirty;
}
