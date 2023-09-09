#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"
// #include "vec3.h"

class sphere : public surface
{
public:
    sphere() {}
    sphere(point3d cen, float r) : center(cen), radius(r){};

    virtual bool hit(
        ray &r, float t_min, float t_max, hit_record &rec) const override;

public:
    point3d center;
    float radius;
};

bool sphere::hit(ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3d oc = r.origin() - center;
    float a = r.direction().length_squared();
    float b_half = vec3d::dot(oc, r.direction());
    float c = oc.length_squared() - radius * radius;

    float discriminant = b_half * b_half - a * c; // b^2 - 4ac = b_half^2 - ac

    if (discriminant < 0)
        return false;
    float sqrtd = sqrt(discriminant);

    float root = (-b_half - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-b_half + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3d outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

#endif