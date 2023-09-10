#ifndef VEC3D_H
#define VEC3D_H

#include <cmath>
#include <iostream>

#include "utility.h"

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

    std::ostream &operator<<(std::ostream &out)
    {
        return out << e[0] << ' ' << e[1] << ' ' << e[2];
    }

    vec3d operator+(const vec3d &v)
    {
        return vec3d(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
    }

    vec3d operator-(const vec3d &v)
    {
        return vec3d(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
    }

    vec3d operator*(const vec3d &v)
    {
        return vec3d(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
    }

    vec3d operator*(float t)
    {
        return vec3d(t * e[0], t * e[1], t * e[2]);
    }

    vec3d operator/(float t)
    {
        return *this * (1 / t);
    }

    static float dot(const vec3d &v1, const vec3d &v2)
    {
        return v1.e[0] * v2.e[0] +
               v1.e[1] * v2.e[1] +
               v1.e[2] * v2.e[2];
    }

    vec3d cross(const vec3d &u, const vec3d &v)
    {
        return vec3d(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                     u.e[2] * v.e[0] - u.e[0] * v.e[2],
                     u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    float length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    float length() const
    {
        return sqrt(length_squared());
    }

    static vec3d unit_vector(vec3d v)
    {
        return v / v.length();
    }

    static vec3d random_in_unit_sphere()
    {
        while (true)
        {
            vec3d p = vec3d::random(-1, 1);
            if (p.length_squared() < 1)
                return p;
        }
    }

    static vec3d random_unit_vector()
    {
        return unit_vector(random_in_unit_sphere());
    }

    static vec3d random_on_hemisphere(const vec3d &normal)
    {
        vec3d on_unit_sphere = random_unit_vector();
        if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
            return on_unit_sphere;
        else
            return -on_unit_sphere;
    }

    static vec3d random()
    {
        return vec3d(random_float(), random_float(), random_float());
    }

    static vec3d random(float min, float max)
    {
        return vec3d(random_float(min, max), random_float(min, max), random_float(min, max));
    }

public:
    float e[3];
};

// Type aliases for vec3d
using point3d = vec3d; // 3D point
using color = vec3d;   // RGB color

#endif