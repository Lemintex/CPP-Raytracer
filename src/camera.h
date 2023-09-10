#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"

class camera
{
private:
    vec3d origin;
    vec3d horizontal;
    vec3d vertical;
    vec3d lower_left_corner;

public:
    camera()
    {
        // camera
        float aspect_ratio = 16.0 / 9.0;
        float viewport_height = 2.0;
        float viewport_width = aspect_ratio * viewport_height;
        float focal_length = 1.0;

        origin = vec3d(0, 0, 0);
        horizontal = vec3d(viewport_width, 0, 0);
        vertical = vec3d(0, viewport_height, 0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3d(0, 0, focal_length);
    };

    ray get_ray(float u, float v)
    {
        return ray(origin, lower_left_corner + (horizontal * u) + (vertical * v) - origin);
    }
};
#endif