#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>

// using declarations
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constants

const double infinity = std::numeric_limits<float>::infinity();
const double pi = 3.141592653; // is this accurate enough? 5897932385;

// returns the float value of degrees converted to radians
inline float degrees_to_radians(float degrees)
{
    return degrees * pi / 180.0;
}

// returns the value of a float clamped between 0 and 1
inline float random_float()
{
    return rand() / (RAND_MAX + 1.0);
}

// returns the value of a float clamped between min and max
inline float random_float(float min, float max)
{
    return min + (max - min) * random_float();
}

// common headers

#include "ray.h"
#include "vec3d.h"

#endif