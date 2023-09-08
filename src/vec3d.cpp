#include "vec3d.h"

inline std::ostream &operator<<(std::ostream &out, const vec3d &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3d operator+(const vec3d &u, const vec3d &v)
{
    return vec3d(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3d operator-(const vec3d &u, const vec3d &v)
{
    return vec3d(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3d operator*(const vec3d &u, const vec3d &v)
{
    return vec3d(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3d operator*(float t, const vec3d &v)
{
    return vec3d(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3d operator*(const vec3d &v, float t)
{
    return t * v;
}

inline vec3d operator/(vec3d v, float t)
{
    return (1 / t) * v;
}

inline double dot(const vec3d &u, const vec3d &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3d cross(const vec3d &u, const vec3d &v)
{
    return vec3d(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                 u.e[2] * v.e[0] - u.e[0] * v.e[2],
                 u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3d unit_vector(vec3d v)
{
    return v / v.length();
}
