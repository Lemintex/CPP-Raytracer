#ifndef SURFACE_LIST_H
#define SURFACE_LIST_H

#include "surface.h"

class surface_list : public surface
{
public:
    surface_list() {}
    surface_list(surface **l, int n) {list = l; list_size = n;}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    surface **list;
    int list_size;
};

#endif