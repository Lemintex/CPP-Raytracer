#include "sphere.h"

bool sphere::hit(ray &r, interval ray_t, hit_record &rec) const
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
    if (root < ray_t.min || ray_t.max < root)
    {
        root = (-b_half + sqrtd) / a;
        if (root < ray_t.min || ray_t.max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3d outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}
