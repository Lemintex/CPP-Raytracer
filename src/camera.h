#ifndef CAMERA_H
#define CAMERA_H

#include "vec3d.h"
#include "ray.h"
#include "utility.h"
#include "surface.h"

class camera
{
public:
    int bounce_limit = 50;
    vec3d origin;
    vec3d horizontal;
    vec3d vertical;
    vec3d lower_left_corner;

public:
    camera();

    ray get_ray(float u, float v);

    color ray_color(ray &r, const surface &world, int bounce_limit);
};
#endif