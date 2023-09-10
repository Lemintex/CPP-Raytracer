#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"
// #include "vec3.h"

class sphere : public surface
{
public:
    point3d center;
    float radius;

public:
    sphere() {}
    sphere(point3d cen, float r) : center(cen), radius(r){};

    virtual bool hit(
        ray &r, float t_min, float t_max, hit_record &rec) const override;
};

#endif