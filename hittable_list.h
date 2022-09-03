#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

struct hittable_list : public hittable {
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(ray const& r, double t_min, double t_max, hit_record& rec) const override;
};

bool hittable_list::hit(ray const& r, double t_min, double t_max, hit_record& rec) const {
    hit_record local_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for(std::shared_ptr<hittable> const& object : objects) {
        if(object->hit(r, t_min, closest_so_far, local_rec)) {
            hit_anything = true;
            closest_so_far = local_rec.t;
            rec = local_rec;
        }
    }

    return hit_anything;
}