//
// Created by andyroiiid on 7/16/2021.
//

#include "tracing/world.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "hittables/sphere.h"
#include "hittables/rect.h"
#include "materials/diffuse_material.h"
#include "materials/metal_material.h"
#include "materials/glass_material.h"

World::World() {
    std::shared_ptr<Material> metal = std::make_shared<MetalMaterial>(glm::vec3{0.8f, 0.8f, 0.8f}, 0.3);
    objects.add(std::make_shared<Sphere>(glm::dvec3{-1.0, 0.0, 0.0}, 0.5, metal));

    std::shared_ptr<Material> blue = std::make_shared<DiffuseMaterial>(glm::vec3{0.4f, 0.8f, 1.0f});
    objects.add(std::make_shared<Sphere>(glm::dvec3{0.0, 0.0, 0.0}, 0.5, blue));
    objects.add(std::make_shared<XYRect>(0.0, 0.0, 1.0, 1.0, -1.0, true, blue));
    objects.add(std::make_shared<YZRect>(0.0, 0.0, 1.0, 1.0, -1.0, true, blue));
    objects.add(std::make_shared<XZRect>(0.0, 0.0, 1.0, 1.0, 1.0, true, blue));

    std::shared_ptr<Material> glass = std::make_shared<GlassMaterial>(1.5);
    objects.add(std::make_shared<Sphere>(glm::dvec3{1.0, 0.0, 0.0}, 0.5, glass));
    objects.add(std::make_shared<Sphere>(glm::dvec3{1.0, 0.0, 0.0}, -0.48, glass));

    std::shared_ptr<Material> ground = std::make_shared<DiffuseMaterial>(glm::vec3{0.5f, 0.5f, 0.5f});
    objects.add(std::make_shared<Sphere>(glm::dvec3{0.0, -1000.5, 0.0}, 1000.0, ground));
}

bool World::ui() {
    bool dirty = false;

    if (ImGui::ColorEdit3("sky color", glm::value_ptr(skyColor))) {
        dirty = true;
    }

    return dirty;
}
