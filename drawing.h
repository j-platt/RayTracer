#pragma once

#include "rt_weekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(ray const& r, hittable const& world, unsigned depth) {
    hit_record rec;

    if(depth == 0) {
        return color{ 0, 0, 0 };
    }

    if(world.hit(r, 0.001, infinity, rec)) {
        return rec.color;
        point3 const target = rec.point + rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.point, target - rec.point), world, depth - 1);
    }

    double const t = 0.5 * (unit_vector(r.direction).y + 1.0);
    return (1.0 - t) * color { 1.0, 1.0, 1.0 } + t * color{ 0.5, 0.7, 1.0 };
}

// Image properties
constexpr double  aspect_ratio = 16.0 / 9.0;
constexpr unsigned image_width = 400;
//constexpr unsigned image_width = 1920;
constexpr unsigned image_height = static_cast<unsigned>(image_width / aspect_ratio);;
constexpr unsigned samples_per_pixel = 10;
constexpr unsigned max_depth = 50;

void draw_screen(HDC hdc) {
    // World

    hittable_list world;
    world.add(std::make_shared<sphere>(point3{ 0, 0, -1 }, .9, color{ 1, 1, 0 }));
    world.add(std::make_shared<sphere>(point3{ 0, -100.5, -1 }, 100, color{ 1, 0, 0 }));

    // Camera

    camera cam;
    
    for(unsigned row = 0; row <= image_height - 1; row++) {
        for(unsigned column = 0; column < image_width; ++column) {
            color pixel_color{ 0, 0, 0 };
            for(unsigned sample = 0; sample < samples_per_pixel; ++sample) {
                double const u = (column + random_double()) / (image_width - 1);
                double const v = (row + random_double()) / (image_height - 1);
                ray const r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(hdc, column, row, pixel_color, samples_per_pixel);
        }
    }
}