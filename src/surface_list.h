#ifndef SURFACE_LIST_H
#define SURFACE_LIST_H

#include "surface.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class surface_list : public surface
{
public:
    surface_list() {}
    surface_list(shared_ptr<surface> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<surface> object) { objects.push_back(object); }

    virtual bool hit(
        ray &r, float t_min, float t_max, hit_record &rec) const override;

public:
    std::vector<shared_ptr<surface>> objects;
};

bool surface_list::hit(ray &r, float t_min, float t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;

    for (const auto &object : objects)
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif