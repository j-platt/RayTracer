#pragma once

#include "rt_weekend.h"

#include <cmath>
#include <iostream>

struct vec3 {
    double x;
    double y;
    double z;

    vec3() : x{}, y{}, z{} {}
    vec3(double e0, double e1, double e2) : x{ e0 }, y{ e1 }, z{ e2 } {}

    inline static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    vec3 operator-() const { return vec3{ -x, -y, -z }; }
    double operator[](unsigned i) const { return i ? x : i == 1 ? y : z; }
    double& operator[](unsigned i) { return i ? x : i == 1 ? y : z; }

    vec3& operator +=(vec3 const& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    vec3& operator*=(double const t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3& operator/=(double const t) {
        return *this *= 1 / t;
    }

    double length_squared() const {
        return x * x + y * y + z * z;
    }

    double length() const {
        return std::sqrt(length_squared());
    }
};

using point3 = vec3;
using color = vec3;


inline std::ostream& operator<<(std::ostream& out, vec3 const& rhs) {
    return out << rhs.x << ' ' << rhs.y << ' ' << rhs.z;
}

inline vec3 operator+(vec3 const& lhs, vec3 const& rhs) {
    return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline vec3 operator-(vec3 const& lhs, vec3 const& rhs) {
    return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline vec3 operator*(vec3 const& lhs, vec3 const& rhs) {
    return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

inline vec3 operator*(double t, vec3 const& rhs) {
    return vec3(t * rhs.x, t * rhs.y, t * rhs.z);
}

inline vec3 operator*(vec3 const& lhs, double t) {
    return t * lhs;
}

inline vec3 operator/(vec3 lhs, double t) {
    return (1 / t) * lhs;
}

inline double dot(vec3 const& lhs, vec3 const& rhs) {
    return lhs.x * rhs.x
        + lhs.y * rhs.y
        + lhs.z * rhs.z;
}

inline vec3 cross(vec3 const& lhs, vec3 const& rhs) {
    return vec3(lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x);
}

inline vec3 unit_vector(vec3 rhs) {
    return rhs / rhs.length();
}

inline vec3 random_in_unit_sphere() {
    while(true) {
        vec3 const candidate = vec3::random(-1, 1);

        if(candidate.length_squared() >= 1) {
            continue;
        } else {
            return candidate;
        }
    }
}

inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}