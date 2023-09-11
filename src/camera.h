#ifndef CAMERA_H
#define CAMERA_H

#include <iomanip>
#include <iostream>

#include "vec3d.h"
#include "color.h"
#include "ray.h"
#include "utility.h"
#include "surface.h"

class camera
{
private:
    int samples_per_pixel = 10;
    int bounce_limit = 10;
    int image_width = 2160;
    int image_height = static_cast<int>(image_width / 16.0 * 9.0);
    ray get_ray(float u, float v);

    color ray_color(ray &r, const surface &world, int bounce_limit);

public:
    camera();

    void init();

    void render(const surface &world);

public:
    vec3d origin;
    vec3d horizontal;
    vec3d vertical;
    vec3d lower_left_corner;
};

#endif