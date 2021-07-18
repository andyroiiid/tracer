//
// Created by andyroiiid on 7/18/2021.
//

#include "hittables/rect.h"

HitRecord XYRect::hit(const Ray &ray, double tMin, double tMax) const {
    double t = (k - ray.origin.z) / ray.direction.z;
    if (t < tMin || t > tMax) return HitRecord();

    double x = ray.origin.x + t * ray.direction.x;
    double y = ray.origin.y + t * ray.direction.y;
    if (x < x0 || x > x1 || y < y0 || y > y1) return HitRecord();

    return HitRecord(t, ray, {0.0, 0.0, facingPos ? 1.0 : -1.0}, material);
}

HitRecord YZRect::hit(const Ray &ray, double tMin, double tMax) const {
    double t = (k - ray.origin.x) / ray.direction.x;
    if (t < tMin || t > tMax) return HitRecord();

    double y = ray.origin.y + t * ray.direction.y;
    double z = ray.origin.z + t * ray.direction.z;
    if (y < y0 || y > y1 || z < z0 || z > z1) return HitRecord();

    return HitRecord(t, ray, {facingPos ? 1.0 : -1.0, 0.0, 0.0}, material);
}

HitRecord XZRect::hit(const Ray &ray, double tMin, double tMax) const {
    double t = (k - ray.origin.y) / ray.direction.y;
    if (t < tMin || t > tMax) return HitRecord();

    double x = ray.origin.x + t * ray.direction.x;
    double z = ray.origin.z + t * ray.direction.z;
    if (x < x0 || x > x1 || z < z0 || z > z1) return HitRecord();

    return HitRecord(t, ray, {0.0, facingPos ? 1.0 : -1.0, 0.0}, material);
}
