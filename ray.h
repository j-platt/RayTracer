#pragma once

#include "vec3.h"

struct ray {
    point3 origin;
    vec3 direction;

    ray() {}
    ray(point3 const& origin, vec3 const& direction)
        : origin(origin), direction(direction) {}

    point3 at(double t) const {
        return origin + t * direction;
    }
};