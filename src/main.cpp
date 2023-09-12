#include <iostream>

#include "camera.h"
#include "utility.h"
#include "color.h"
#include "surface_list.h"
#include "sphere.h"

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
              << cam.image_width << " " << cam.image_height << "\n255\n";

    cam.render(world);
    std::cerr << "\nDone!\n";
}