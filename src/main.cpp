#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3d.h"

float hit_sphere(const vec3d &center, float radius, const ray &r)
{
    vec3d oc = r.origin() - center;
    float a = vec3d::dot(r.direction(), r.direction());
    float b = 2.0 * vec3d::dot(oc, r.direction());
    float c = vec3d::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c; // b^2 - 4ac
    if (discriminant < 0)
        return -1.0;
    else
        return (-b - sqrt(discriminant)) / (2.0 * a);
}

color ray_color(ray &r)
{
    float t = hit_sphere(vec3d(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3d N = vec3d::unit_vector(r.at(t) - vec3d(0, 0, -1));
        return color(N.x() + 1, N.y() + 1, N.z() + 1) / 2.0;
    }
    vec3d unit_direction = vec3d::unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0) * (1 - t) + color(0.5, 0.7, 1.0) * t;
}

// created left->right, top->bottom
int main()
{
    // dimensions
    const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 2160;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // camera
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0;

    vec3d origin = vec3d(0, 0, 0);
    vec3d horizontal = vec3d(viewport_width, 0, 0);
    vec3d vertical = vec3d(0, viewport_height, 0);
    vec3d lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3d(0, 0, focal_length);

    // render image
    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int i = image_height - 1; i >= 0; i--)
    {
        std::cerr << "Rendering scanline " << image_height - i << " of " << image_height << '\n';
        for (int j = 0; j < image_width; j++)
        {
            float u = float(j) / (image_width - 1);
            float v = float(i) / (image_height - 1);
            ray r(origin, lower_left_corner + ((horizontal * u) + (vertical * v) - origin));
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "Done!\n";
}