#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <limits>
#include <memory>

// Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<float>::infinity();
const double pi = 3.141592653; // is this accurate enough? 5897932385;

// Utility Functions

inline float degrees_to_radians(float degrees)
{
    return degrees * pi / 180.0;
}

// Common Headers

#include "ray.h"
#include "vec3d.h"

#endif