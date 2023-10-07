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
    bool front_face;

    inline void set_face_normal(const ray &r, const vec3d &outward_normal)
    {
        front_face = vec3d::dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class surface
{
public:
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif