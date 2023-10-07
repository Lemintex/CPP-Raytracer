#include "sphere.h"

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3d oc = r.origin() - center;
    float a = vec3d::dot(r.direction(), r.direction());
    float b = vec3d::dot(oc, r.direction());
    float c = vec3d::dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            rec.set_face_normal(r, rec.normal);
            return true;
        }
    }
    return false;
}