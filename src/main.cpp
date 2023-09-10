#include <iostream>
#include <iomanip>

#include "camera.h"
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

    int samples_per_pixel = 1;

    camera cam;

    // world
    surface_list world;
    world.add(make_shared<sphere>(point3d(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3d(0, -100.5, -1), 100));

    // render image
    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int i = image_height - 1; i >= 0; i--)
    {
        for (int j = 0; j < image_width; j++)
        {
            float percent = (i * image_width + j) / (float)(image_width * image_height) * 100.0;
            percent = 100.0 - percent;
            std::cerr << "\rProgress: " << std::fixed << std::setprecision(2) << percent << "% " << std::flush;
            color pixel_color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; s++)
            {
                float u = float(j + random_float()) / (image_width - 1);
                float v = float(i + random_float()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }

            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone!\n";
}