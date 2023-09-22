#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"
#include "interval.h"
// #include "vec3.h"

class sphere : public surface
{
public:
    point3d center;
    float radius;
    material *mat_ptr;

public:
    sphere() {}
    sphere(point3d cen, float r) : center(cen), radius(r){}
    sphere(point3d cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {}

    virtual bool hit(
        ray &r, interval ray_t, hit_record &rec) const override;
};

#endif