#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3d.h"
#include "ray.h"
#include "surface.h"

struct hit_record;

class material
{
public:
    virtual bool scatter(
        ray &r_in, hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

class lambertian : public material
{
public:
    color albedo;

public:
    lambertian(const color &a) : albedo(a) {}

    bool scatter(ray &r_in, hit_record &rec, color &attenuation, ray &scattered) const
    {
        vec3d scatter_direction = rec.normal + vec3d::random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class metal : public material
{
public:
    metal(const color &a) : albedo(a) {}

    bool scatter(ray &r_in, hit_record &rec, color &attenuation, ray &scattered)
        const override
    {
        vec3d uv = vec3d::unit_vector(r_in.direction());
        vec3d reflected = vec3d::reflect(uv, rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

#endif