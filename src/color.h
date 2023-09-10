#ifndef COLOR_H
#define COLOR_H

#include "vec3d.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel)
{
    float s = 1.0 / samples_per_pixel;

    pixel_color /= samples_per_pixel;

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif