#pragma once

#include "hittable.h"

struct sphere : public hittable {
    point3 center;
    double radius;
    color material;

    sphere() : center(), radius{} {}
    sphere(point3 center, double radius) : center(center), radius(radius) {};
    sphere(point3 center, double radius, color color) : center(center), radius(radius), material(color) {};

    virtual bool hit(ray const& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(ray const& r, double t_min, double t_max, hit_record& rec) const {
    vec3 const oc = r.origin - center;
    double const a = r.direction.length_squared();
    double const half_b = dot(oc, r.direction);
    double const c = oc.length_squared() - radius * radius;
    double const discriminant = half_b * half_b - 4 * a * c;

    if(discriminant < 0) {
        return false;
    }

    double const sqrt_discriminant = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double const minus_root = (-half_b - sqrt_discriminant) / a;
    double const plus_root = (-half_b + sqrt_discriminant) / a;
    if(minus_root < t_min || minus_root > t_max) {
        if(plus_root < t_min || plus_root > t_max) {
            return false;
        }
    }

    rec.color = material;
    rec.t = plus_root;
    rec.point = r.at(plus_root);
    vec3 outward_normal = (rec.point - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}