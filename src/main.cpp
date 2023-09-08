#include <iostream>

#include "color.h"
#include "vec3d.h"

// created left->right, top->bottom
int main()
{
    // dimensions
    const int image_width = 2160;
    const int image_height = 1440;

    // render image
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int i = image_height - 1; i >= 0; i--)
    {
        std::cerr << "Rendering scanline " << image_height - i << " of " << image_height << '\n';
        for (int j = 0; j < image_width; j++)
        {
            color pixel_color(float(i) / (image_width - 1), float(j) / (image_height - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "Done!\n";
}