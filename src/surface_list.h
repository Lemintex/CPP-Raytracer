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
    std::vector<shared_ptr<surface>> objects;

public:
    surface_list() {}
    surface_list(shared_ptr<surface> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<surface> object) { objects.push_back(object); }

    virtual bool hit(
        ray &r, float t_min, float t_max, hit_record &rec) const override;
};

#endif