#include <iostream>

#include "utility.h"
#include "color.h"
#include "surface_list.h"
#include "sphere.h"

color ray_color(ray &r, const surface &world)
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec))
    {
        return (rec.normal + color(1, 1, 1)) / 2;
    }
    vec3d unit_direction = vec3d::unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0) * (1 - t) + color(0.5, 0.7, 1.0) * t;
}

// created left->right, top->bottom
int main()
{
    // dimensions
    const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 2160;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // world
    surface_list world;
    world.add(make_shared<sphere>(point3d(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3d(0, -100.5, -1), 100));

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
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "Done!\n";
}