#include <iostream>

#include "vec3d.h"
#include "ray.h"
#include "surface.h"
#include "surface_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

float hit_sphere(const vec3d &center, float radius, const ray &r)
{
    vec3d oc = r.origin() - center;
    float a = vec3d::dot(r.direction(), r.direction());
    float b = 2.0 * vec3d::dot(oc, r.direction());
    float c = vec3d::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    } 
}

vec3d get_color(const ray &r, const surface &world, int depth = 0)
{
    hit_record rec;
    if (world.hit(r, 0.00001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3d attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * get_color(scattered, world, depth - 1);
        }
        else
        {
            return vec3d(0, 0, 0);
        }
        vec3d target = rec.p + rec.normal + vec3d::random_in_unit_sphere();
        return get_color(ray(rec.p, target - rec.p), world) * 0.5;
    }
    vec3d unit_direction = vec3d::unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return vec3d(1.0, 1.0, 1.0) * (1.0 - t) + vec3d(0.5, 0.7, 1.0) * t;
}

surface_list *generateScene()
{
   int n = 500;
    surface **list = new surface*[n+1];
    list[0] = new sphere(vec3d(0,-1000,0), 1000, new lambertian(vec3d(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            float choose_mat = drand48();
            vec3d center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - vec3d(4, 0.2, 0)).length() > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3d(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
                }
                else if (choose_mat < 0.95)
                {
                    list[i++] = new sphere(center, 0.2, new metal(vec3d(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
                }
                else
                {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3d(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3d(-4, 1, 0), 1.0, new lambertian(vec3d(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3d(4, 1, 0), 1.0, new metal(vec3d(0.7, 0.6, 0.5), 0.0));

    return new surface_list(list, i); 
}

int main()
{
    surface_list *world = generateScene();

    vec3d lookfrom(13,2,3);
    vec3d lookat(0,0,0);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperture = 0.0;
    camera cam = camera(lookfrom, lookat, vec3d(0,1,0), 40, 16.0/9.0, aperture, dist_to_focus);

    
    cam.render(*world);
}