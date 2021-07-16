//
// Created by andyroiiid on 7/16/2021.
//

#include "world.h"

#include "sphere.h"
#include "diffuse_material.h"
#include "metal_material.h"
#include "glass_material.h"

World::World() {
    std::shared_ptr<Material> metal = std::make_shared<MetalMaterial>(glm::dvec3{0.8, 0.8, 0.8}, 0.3);
    add(std::make_shared<Sphere>(glm::dvec3{-1.0, 0.0, 0.0}, 0.5, metal));

    std::shared_ptr<Material> blue = std::make_shared<DiffuseMaterial>(glm::dvec3{0.4, 0.8, 1.0});
    add(std::make_shared<Sphere>(glm::dvec3{0.0, 0.0, 0.0}, 0.5, blue));

    std::shared_ptr<Material> glass = std::make_shared<GlassMaterial>(1.5);
    add(std::make_shared<Sphere>(glm::dvec3{1.0, 0.0, 0.0}, 0.5, glass));
    add(std::make_shared<Sphere>(glm::dvec3{1.0, 0.0, 0.0}, -0.48, glass));

    std::shared_ptr<Material> ground = std::make_shared<DiffuseMaterial>(glm::dvec3{0.5, 0.5, 0.5});
    add(std::make_shared<Sphere>(glm::dvec3{0.0, -1000.5, 0.0}, 1000.0, ground));
}
