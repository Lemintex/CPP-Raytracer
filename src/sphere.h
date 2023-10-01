#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"
#include "ray.h"
#include "vec3d.h"

class material;

class sphere : public surface
{
public:
    sphere() {}
    sphere(vec3d cen, float r) {center = cen; radius = r; }
    sphere(vec3d cen, float r, material *m) {center = cen; radius = r; mat_ptr = m; }

    vec3d center;
    float radius;
    material *mat_ptr;
    
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;
};

#endif