#ifndef CAMERA_H
#define CAMERA_H

#include "vec3d.h"
#include "ray.h"
#include "utility.h"

class camera
{
public:
    vec3d origin;
    vec3d horizontal;
    vec3d vertical;
    vec3d lower_left_corner;

public:
    camera();

    ray get_ray(float u, float v);
};
#endif