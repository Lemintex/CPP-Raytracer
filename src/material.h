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
        metal(const vec3d &a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3d &attenuation, ray &scattered) const override
        {
            vec3d reflected = vec3d::reflect(vec3d::unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + vec3d::random_unit_vector() * fuzz);
            attenuation = albedo;
            return (vec3d::dot(scattered.direction(), rec.normal) > 0);
        }

        vec3d albedo;
        float fuzz;
};

class dielectric : public material
{
    public:
    dielectric(float ir)
    {
        refraction_index = ir;
    }

    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3d &attenuation, ray &scattered) const override
    {
        vec3d outward_normal;
        vec3d reflected = vec3d::reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = vec3d(1.0, 1.0, 0.0);
        vec3d refracted;
        if (vec3d::dot(r_in.direction(), rec.normal) > 0)
        {
            outward_normal = -rec.normal;
            ni_over_nt = refraction_index;
        }
        else
        {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / refraction_index;
        }

        if (vec3d::refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
        {
            scattered = ray(rec.p, refracted);
        }
        else
        {
            scattered = ray(rec.p, reflected);
            return false;
        }
        return true;
        // attenuation = vec3d(1.0, 1.0, 1.0);
        // float refraction_ratio = rec.t ? (1.0 / ir) : ir;

        // vec3d unit_direction = vec3d::unit_vector(r_in.direction());
        // vec3d refracted = vec3d::refract(r_in.direction(), rec.normal, refraction_ratio);
        //     scattered = ray(rec.p, refracted);
        return true;
    }

    double refraction_index; // Index of Refraction
};

#endif