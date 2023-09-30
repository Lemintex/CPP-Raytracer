#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3d.h"
#include "surface.h"

class material
{
    public:
        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3d &attenuation, ray &scattered) const = 0;

};

class lambertian : public material
{
    public:
        lambertian(const vec3d &a) : albedo(a) {}

        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3d &attenuation, ray &scattered) const override
        {
            vec3d scatter_direction = rec.normal + vec3d::random_unit_vector();
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

        vec3d albedo;
};

class metal : public material
{
    public:
        metal(const vec3d &a) : albedo(a) {}

        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3d &attenuation, ray &scattered) const override
        {
            vec3d reflected = vec3d::reflect(vec3d::unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (vec3d::dot(scattered.direction(), rec.normal) > 0);
        }

        vec3d albedo;
};
#endif