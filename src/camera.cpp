#include "camera.h"

camera::camera()
{
    // camera
    float aspect_ratio = 16.0 / 9.0;
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0;

    origin = vec3d(0, 0, 0);
    horizontal = vec3d(viewport_width, 0, 0);
    vertical = vec3d(0, viewport_height, 0);
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3d(0, 0, focal_length);
};

ray camera::get_ray(float u, float v)
{
    return ray(origin, lower_left_corner + (horizontal * u) + (vertical * v) - origin);
}

color camera::ray_color(ray &r, const surface &world, int limit)
{
    if (limit <= 0)
    {
        return color(0, 0, 0);
    }
    hit_record rec;
    if (world.hit(r, interval(0.001, infinity), rec))
    {
        vec3d direction = vec3d::random_on_hemisphere(rec.normal);
        ray scattered = ray(rec.p, direction);
        color c = ray_color(scattered, world, limit - 1) * 0.5;
        return c;
        return (rec.normal + color(1, 1, 1)) / 2;
    }
    vec3d unit_direction = vec3d::unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0) * (1 - t) + color(0.5, 0.7, 1.0) * t;
}