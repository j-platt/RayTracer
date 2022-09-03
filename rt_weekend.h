#pragma once

#include <Windows.h>

#include <cmath>
#include <limits>
#include <memory>
#include <random>

constexpr double const infinity = std::numeric_limits<double>::infinity();
constexpr double const pi = 3.1415926535897832385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double(double min, double max) {
    std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double() {
    return random_double(0.0, 1.0);
}

inline double clamp(double x, double min, double max) {
    return x < min ? min : x > max ? max : x;
}

//void draw_screen() {
//    // Image
//
//    constexpr double  aspect_ratio = 16.0 / 9.0;
//    constexpr unsigned image_width = 400;
//    constexpr unsigned image_height = static_cast<unsigned>(image_width / aspect_ratio);;
//    constexpr unsigned samples_per_pixel = 100;
//    constexpr unsigned max_depth = 50;
//
//    // World
//
//    hittable_list world;
//    world.add(std::make_shared<sphere>(point3{ 0, 0, -1 }, 0.9));
//    world.add(std::make_shared<sphere>(point3{ 0, -100.5, -1 }, 100));
//
//    // Camera
//
//    camera cam;
//    //for(unsigned row = image_height - 1; row-- > 0;)
//    //{
//    //    std::cerr << "\rScanlines remaining: " << row << ' ' << std::flush;
//    //    for(unsigned column = 0; column < image_width; ++column) {
//    //        color pixel_color{ 0, 0, 0 };
//    //        for(unsigned sample = 0; sample < samples_per_pixel; ++sample) {
//    //            double const u = (column + random_double()) / (image_width - 1);
//    //            double const v = (row + random_double()) / (image_height - 1);
//    //            ray const r = cam.get_ray(u, v);
//    //            pixel_color += ray_color(r, world, max_depth);
//    //        }
//    //        write_color(std::cout, pixel_color, samples_per_pixel);
//    //    }
//    //}
//}