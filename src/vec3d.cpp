#include "vec3d.h"

// methods with vec3d
inline vec3d operator+(const vec3d &v1, const vec3d &v2) {
    return vec3d(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3d operator-(const vec3d &v1, const vec3d &v2) {
    return vec3d(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3d operator*(const vec3d &v1, const vec3d &v2) {
    return vec3d(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3d operator/(const vec3d &v1, const vec3d &v2) {
    return vec3d(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1],v1.e[2] / v2.e[2]);
}

// methods with float
inline vec3d operator*(float t, const vec3d &v) {
    return vec3d(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3d operator*(const vec3d &v,float t) {
    return vec3d(t * v.e[0], t * v.e[1],t * v.e[2]);
}

inline vec3d operator/(float t, const vec3d &v) {
    return vec3d(t / v.e[0], t / v.e[1], t / v.e[2]);
}

inline vec3d operator/(const vec3d &v, float t) {
    return vec3d(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

// operators with vec3d
inline vec3d &vec3d::operator+=(const vec3d &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3d &vec3d::operator-=(const vec3d &v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline vec3d &vec3d::operator*=(const vec3d &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline vec3d &vec3d::operator/=(const vec3d &v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

// operators with float
inline vec3d &vec3d::operator+=(const float t)
{
    e[0] += t;
    e[1] += t;
    e[2] += t;
    return *this;
}

inline vec3d &vec3d::operator-=(const float t)
{
    e[0] -= t;
    e[1] -= t;
    e[2] -= t;
    return *this;
}

inline vec3d &vec3d::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3d &vec3d::operator/=(const float t)
{
    return *this *= 1 / t;
}

inline std::ostream& operator<<(std::ostream &os, vec3d &t) {
 os << t.e[0] << " " << t.e[1] << " " << t.e[2];
 return os;
}

// inline vec3d vec3d::operator+(const vec3d &v)
// {
//     return vec3d(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
// }

// inline vec3d vec3d::operator-(const vec3d &v)
// {
//     return vec3d(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
// }

// inline vec3d vec3d::operator*(const vec3d &v)
// {
//     return vec3d(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
// }

// inline vec3d vec3d::operator/(const vec3d &v)
// {
//     return vec3d(e[0] / v.e[0], e[1] / v.e[1], e[2] / v.e[2]);
// }

// inline vec3d vec3d::operator+(float t)
// {
//     return vec3d(t + e[0], t + e[1], t + e[2]);
// }

// inline vec3d vec3d::operator-(float t)
// {
//     return vec3d(e[0] - t, e[1] - t, e[2] - t);
// }

// inline vec3d vec3d::operator*(float t)
// {
//     return vec3d(t * e[0], t * e[1], t * e[2]);
// }

// inline vec3d vec3d::operator/(float t)
// {
//     return *this * (1 / t);
// }

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

static vec3d random_vec3d()
{
    return vec3d(random_float(), random_float(), random_float());
}

static vec3d random(float min, float max)
{
    return vec3d(random_float(min, max), random_float(min, max), random_float(min, max));
}
