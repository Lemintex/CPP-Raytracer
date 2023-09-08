#ifndef RAY_H
#define RAY_H

#include "vec3d.h"

class ray
{
public:
    ray() {}
    ray(const vec3d &origin, const vec3d &direction)
        : orig(origin), dir(direction)
    {
    }

    vec3d origin() const { return orig; }
    vec3d direction() const { return dir; }

    vec3d at(float t)
    {
        return orig + (dir * t);
    }

public:
    vec3d orig;
    vec3d dir;
};

#endif