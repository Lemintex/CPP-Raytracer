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

int main()
{
    int samples = 10;
    camera cam;
    int width = 2160;
    int height = static_cast<int>(width / 16.0 * 9.0);

    surface *list[3];
    material* mat = new metal(vec3d(0.5, 0.5, 0.8), 0.2);
    list[0] = new sphere(vec3d(0.5, 0, -1), 0.5, mat);
    material* mat2 = new lambertian(vec3d(0.8, 0.3, 0.3));
    list[1] = new sphere(vec3d(0, -101, -2), 100, mat2);
    material* mat3 = new metal(vec3d(0.7, 0.6, 1), 0.5);
    list[2] = new sphere(vec3d(-0.5, 0, -1), 0.5, mat3);

    surface_list world(list, 3);
    cam = camera();

    vec3d lower_left_corner(-2.0, -1.0, -1.0);
    vec3d horizontal(4.0, 0.0, 0.0);
    vec3d vertical(0.0, 2.0, 0.0);
    vec3d origin(0.0, 0.0, 0.0);

    std::cout << "P3\n" << width << " " << height << "\n255\n";
        for (int i = height - 1; i >= 0; i--)
        {
            std::cerr << "\rScanlines remaining: " << i << " " << std::flush;
            for (int j = 0; j < width; j++)
            {
                vec3d color(0, 0, 0);
                for (int s = 0; s < samples; s++)
                {
                    float u = float(j + drand48()) / width;
                    float v = float(i + drand48()) / height;
                    // ray r(origin, lower_left_corner + horizontal * u + vertical * v);
                ray r = cam.get_ray(u, v);
                    color += get_color(r, world);
                }
                color /= samples;
                color = vec3d(sqrt(color.x()), sqrt(color.y()), sqrt(color.z()));
                int ir = static_cast<int>(255.999 * color.x());
                int ig = static_cast<int>(255.999 * color.y());
                int ib = static_cast<int>(255.999 * color.z());
                std::cout << ir << " " << ig << " " << ib << "\n";
            }
        }   
}