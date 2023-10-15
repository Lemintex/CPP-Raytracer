#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec3d.h"
#include "surface.h"   
#include "surface_list.h"
#include "material.h"

class camera {
public:
    camera() {}
    camera(vec3d lookfrom, vec3d lookat, vec3d vup, float vfov, float aspect_ratio, float aperture, float focus_dist);
    ray get_ray(float u, float v) const
    {
        return ray(origin, lower_left_corner + horizontal * u + vertical * v - origin);
    }

    vec3d get_color(const ray &r, const surface &world, int bounce_limit);

    void render(const surface_list &world);

    float aspect_ratio = 16.0/9.0;

    int image_width = 2160;
    int image_height = static_cast<int>(image_width / aspect_ratio);

    int samples_per_pixel = 10;
    int bounce_limit = 10;
    
    vec3d lower_left_corner, horizontal, vertical, origin;
    vec3d u, v, w;
    float lens_radius;
};

#endif