#pragma once

#include "vec3.h"

#include <iostream>

void write_color(HDC hdc, unsigned x, unsigned y, color pixel_color, unsigned samples_per_pixel) {
    double const scale = (1.0 / samples_per_pixel);

    pixel_color.x = std::sqrt(pixel_color.x * scale);
    pixel_color.y = std::sqrt(pixel_color.y * scale);
    pixel_color.z = std::sqrt(pixel_color.z * scale);

    SetPixel(hdc, x, y, RGB(static_cast<unsigned>(256 * clamp(pixel_color.x, 0.0, 0.999)),
        static_cast<unsigned>(256 * clamp(pixel_color.y, 0.0, 0.999)),
        static_cast<unsigned>(256 * clamp(pixel_color.z, 0.0, 0.999))));

    //// Write the translated [0,255] value of each color component.
    //out << static_cast<unsigned>(256 * clamp(pixel_color.x, 0.0, 0.999)) << ' '
    //    << static_cast<unsigned>(256 * clamp(pixel_color.y, 0.0, 0.999)) << ' '
    //    << static_cast<unsigned>(256 * clamp(pixel_color.z, 0.0, 0.999)) << '\n';
}
