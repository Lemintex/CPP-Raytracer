#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3d
{
    public:
    vec3d() {}
    vec3d(float e0, float e1, float e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    float e[3];
    
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3d &operator+() const { return *this; }
    inline vec3d operator-() const { return vec3d(-e[0], -e[1], -e[2]); }

    inline float operator[](int i) const { return e[i]; }
    inline float &operator[](int i) { return e[i]; }

    // operators with vec3d
    inline vec3d &operator+=(const vec3d &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    inline vec3d &operator-=(const vec3d &v)
    {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

    inline vec3d &operator*=(const vec3d &v)
    {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }

    inline vec3d &operator/=(const vec3d &v)
    {
        e[0] /= v.e[0];
        e[1] /= v.e[1];
        e[2] /= v.e[2];
        return *this;
    }

    // operators with float
    inline vec3d &operator+=(const float t)
    {
        e[0] += t;
        e[1] += t;
        e[2] += t;
        return *this;
    }

    inline vec3d &operator-=(const float t)
    {
        e[0] -= t;
        e[1] -= t;
        e[2] -= t;
        return *this;
    }

    inline vec3d &operator*=(const float t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    inline vec3d &operator/=(const float t)
    {
        float k = 1.0 / t;
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
        return *this;
    }

    inline vec3d operator+(const vec3d &v2) const
    {
        return vec3d(e[0] + v2.e[0],
                    e[1] + v2.e[1],
                    e[2] + v2.e[2]);
    }

    inline vec3d operator-(const vec3d &v2) const
    {
        return vec3d(e[0] - v2.e[0],
                    e[1] - v2.e[1],
                    e[2] - v2.e[2]);
    }

    inline vec3d operator*(const vec3d &v2) const
    {
        return vec3d(e[0] * v2.e[0],
                    e[1] * v2.e[1],
                    e[2] * v2.e[2]);
    }

    inline vec3d operator/(const vec3d &v2) const
    {
        return vec3d(e[0] / v2.e[0],
                    e[1] / v2.e[1],
                    e[2] / v2.e[2]);
    }

    // operators with float
    inline vec3d operator+(const float t) const
    {
        return vec3d(e[0] + t,
                    e[1] + t,
                    e[2] + t);
    }

    inline vec3d operator-(const float t) const
    {
        return vec3d(e[0] - t,
                    e[1] - t,
                    e[2] - t);
    }

    inline vec3d operator*(const float t) const
    {
        return vec3d(e[0] * t,
                    e[1] * t,
                    e[2] * t);
    }

    inline vec3d operator/(const float t) const
    {
        float k = 1.0 / t;
        return vec3d(e[0] * k,
                    e[1] * k,
                    e[2] * k);
    }

    static vec3d unit_vector(const vec3d &v);

    static vec3d random_unit_vector();

    inline float length() const
    {
        return sqrt(e[0] * e[0] +
                    e[1] * e[1] +
                    e[2] * e[2]);
    }
    
    static float dot(const vec3d &v1, const vec3d &v2);

    static vec3d cross(const vec3d &v1, const vec3d &v2);

    static vec3d random_in_unit_sphere();

    inline float squared_length() const
    {
        return e[0] * e[0] +
               e[1] * e[1] +
               e[2] * e[2];
    }

    static vec3d reflect(const vec3d &v, const vec3d &n);

    inline vec3d linear_to_gamma()
    {
        return vec3d(sqrt(x()), sqrt(y()), sqrt(z()));
    }

    static void write_color(std::ostream &out, vec3d pixel_color, int samples_per_pixel)
    {
        float s = 1.0 / samples_per_pixel;

        pixel_color /= samples_per_pixel;

        pixel_color = pixel_color.linear_to_gamma();
        pixel_color = pixel_color.linear_to_gamma();
        
        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(255.999 * pixel_color.x()) << ' '
            << static_cast<int>(255.999 * pixel_color.y()) << ' '
            << static_cast<int>(255.999 * pixel_color.z()) << '\n';
    }

    static bool refract(const vec3d &v, const vec3d &n, float ni_over_nt, vec3d &refracted);

    static float schlick(float cosine, float ref_idx);
};


// Type aliases for vec3d
using point3d = vec3d; // 3D point
using color = vec3d;   // RGB color

#endif