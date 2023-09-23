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
    inline vec3d &operator+=(const vec3d &v);
    inline vec3d &operator-=(const vec3d &v);
    inline vec3d &operator*=(const vec3d &v);
    inline vec3d &operator/=(const vec3d &v);

    // operators with float
    inline vec3d &operator+=(const float t);
    inline vec3d &operator-=(const float t);
    inline vec3d &operator*=(const float t);
    inline vec3d &operator/=(const float t);

    // // methods with vec3d
    // inline vec3d operator+(const vec3d &v);
    // inline vec3d operator-(const vec3d &v);
    // inline vec3d operator*(const vec3d &v);
    // inline vec3d operator/(const vec3d &v);

    // // methods with float
    // inline vec3d operator+(float t);
    // inline vec3d operator-(float t);
    // inline vec3d operator*(float t);
    // inline vec3d operator/(float t);

    static float dot(const vec3d &v1, const vec3d &v2);
    vec3d cross(const vec3d &u, const vec3d &v);
	inline float length() const {return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}
	inline float length_squared() const {return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
    static vec3d unit_vector(vec3d v);
        static vec3d random_in_unit_sphere();
    static vec3d random_unit_vector();
    static vec3d random_on_hemisphere(const vec3d &normal);

    static vec3d random_vec3d();
    static vec3d random(float min, float max);

    // properties
    float e[3];
};

// Type aliases for vec3d
using point3d = vec3d; // 3D point
using color = vec3d;   // RGB color

#endif