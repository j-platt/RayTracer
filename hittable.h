#pragma once

#include "ray.h"

struct hit_record {
    point3 point;
    vec3 normal;
    double t;
    bool front_face;
    color color;

    inline void set_face_normal(ray const& r, vec3 const& outward_normal) {
        front_face = dot(r.direction, outward_normal) > 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

struct hittable {
    virtual bool hit(ray const& r, double t_min, double t_max, hit_record& rec) const = 0;
};