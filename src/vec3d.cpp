#include "vec3d.h"

inline std::ostream &operator<<(std::ostream &os, vec3d &t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

vec3d vec3d::unit_vector(const vec3d &v)
{
    return v / v.length();
}

vec3d vec3d::random_unit_vector()
{
    float a = drand48() * 2 * M_PI;
    float z = drand48() * 2 - 1;
    float r = sqrt(1 - z * z);
    return vec3d(r * cos(a), r * sin(a), z);
}
                                                
float vec3d::dot(const vec3d &v1, const vec3d &v2)
{
    return v1.e[0] * v2.e[0] +
           v1.e[1] * v2.e[1] +
           v1.e[2] * v2.e[2];
}

vec3d vec3d::cross(const vec3d &v1, const vec3d &v2)
{
    return vec3d(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

vec3d vec3d::random_in_unit_sphere()
{
    vec3d p;
    do
    {
        p = vec3d(drand48(), drand48(), drand48()) * 2.0 - vec3d(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

vec3d vec3d::reflect(const vec3d &v, const vec3d &n)
{
    return v - n * 2 * vec3d::dot(v, n);
}

bool vec3d::refract(const vec3d &uv, const vec3d &n, float ni_over_nt, vec3d &refracted)
{
    vec3d unit_v = vec3d::unit_vector(uv);
    float dt = vec3d::dot(unit_v, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = (unit_v - n * dt) * ni_over_nt - n * sqrt(discriminant);
        return true;
    }
    else
    {
        return false;
    }
}

float vec3d::schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}