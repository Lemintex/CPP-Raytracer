#include "ray.h"

vec3d ray::at(float t)
{
    return orig + (dir * t);
}