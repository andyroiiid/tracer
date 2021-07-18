//
// Created by andyroiiid on 7/18/2021.
//

#include "hittables/box.h"

#include "hittables/rect.h"

Box::Box(const glm::dvec3 &p0, const glm::dvec3 &p1, const std::shared_ptr<Material> &material) {
    add(std::make_shared<XYRect>(p0.x, p0.y, p1.x, p1.y, p0.z, false, material));
    add(std::make_shared<XYRect>(p0.x, p0.y, p1.x, p1.y, p1.z, true, material));
    add(std::make_shared<YZRect>(p0.y, p0.z, p1.y, p1.z, p0.x, false, material));
    add(std::make_shared<YZRect>(p0.y, p0.z, p1.y, p1.z, p1.x, true, material));
    add(std::make_shared<XZRect>(p0.x, p0.z, p1.x, p1.z, p0.y, false, material));
    add(std::make_shared<XZRect>(p0.x, p0.z, p1.x, p1.z, p1.y, true, material));
}
