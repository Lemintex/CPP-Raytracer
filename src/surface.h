#ifndef SURFACE_H
#define SURFACE_H

#include "ray.h"
#include "vec3d.h"

class material;

struct hit_record
{
    float t;
    vec3d p;
    vec3d normal;
    material *mat_ptr;
};

class surface
{
public:
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif