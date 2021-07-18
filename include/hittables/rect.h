//
// Created by andyroiiid on 7/18/2021.
//

#ifndef TRACER_RECT_H
#define TRACER_RECT_H

#include "hittables/hittable.h"
#include "materials/material.h"

class XYRect : public Hittable {
public:
    XYRect(double x0, double y0, double x1, double y1, double k, bool facingPos, std::shared_ptr<Material> material)
            : x0(x0), y0(y0), x1(x1), y1(y1), k(k), facingPos(facingPos), material(std::move(material)) {}

    [[nodiscard]] HitRecord hit(const Ray &ray, double tMin, double tMax) const override;

private:
    double x0;
    double y0;
    double x1;
    double y1;
    double k;
    bool facingPos;
    std::shared_ptr<Material> material;
};

class YZRect : public Hittable {
public:
    YZRect(double y0, double z0, double y1, double z1, double k, bool facingPos, std::shared_ptr<Material> material)
            : y0(y0), z0(z0), y1(y1), z1(z1), k(k), facingPos(facingPos), material(std::move(material)) {}

    [[nodiscard]] HitRecord hit(const Ray &ray, double tMin, double tMax) const override;

private:
    double y0;
    double z0;
    double y1;
    double z1;
    double k;
    bool facingPos;
    std::shared_ptr<Material> material;
};

class XZRect : public Hittable {
public:
    XZRect(double x0, double z0, double x1, double z1, double k, bool facingPos, std::shared_ptr<Material> material)
            : x0(x0), z0(z0), x1(x1), z1(z1), k(k), facingPos(facingPos), material(std::move(material)) {}

    [[nodiscard]] HitRecord hit(const Ray &ray, double tMin, double tMax) const override;

private:
    double x0;
    double z0;
    double x1;
    double z1;
    double k;
    bool facingPos;
    std::shared_ptr<Material> material;
};

#endif //TRACER_RECT_H
