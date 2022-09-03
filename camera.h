#pragma once

#include "rt_weekend.h"
#include "ray.h"
#include "vec3.h"

struct camera {
    point3 origin;
    point3 lower_left_corner;
    vec3 right;
    vec3 up;

    camera() {
        constexpr double aspect_ratio = 16.0 / 9.0;
        constexpr double viewport_height = 2.0;
        constexpr double viewport_width = aspect_ratio * viewport_height;
        constexpr double focal_length = 1.0;

        origin = point3{ 0, 0, 0 };
        right = vec3(viewport_width, 0.0, 0.0);
        up = vec3(0.0, -viewport_height, 0.0);
        lower_left_corner = origin - right / 2 - up / 2 - vec3{ 0, 0, focal_length };
    }

    ray get_ray(double u, double v) const {
        return ray(origin, lower_left_corner + u * right + v * up - origin);
    }
};
