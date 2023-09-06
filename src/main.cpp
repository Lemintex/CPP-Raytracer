#include <iostream>

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
            double r = double(i) / (image_width - 1);
            double g = double(j) / (image_height - 1);
            float b = 0.25;

            int ir = 255 * r;
            int ig = 255 * g;
            int ib = 255 * b;

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "Done!\n";
}