#ifndef VEC3D_H
#define VEC3D_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3d
{
public:
    vec3d() : e{0, 0, 0} {}
    vec3d(float e0, float e1, float e2) : e{e0, e1, e2} {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    vec3d operator-() const { return vec3d(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float &operator[](int i) { return e[i]; }

    vec3d &operator+=(const vec3d &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3d &operator*=(const float t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3d &operator/=(const float t)
    {
        return *this *= 1 / t;
    }

    float length() const
    {
        return sqrt(length_squared());
    }

    float length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

public:
    float e[3];
};

// Type aliases for vec3d
using point3 = vec3d; // 3D point
using color = vec3d;  // RGB color

#endif