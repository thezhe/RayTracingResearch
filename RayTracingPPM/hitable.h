#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct record
{
    float t;
    vec3 p;
    vec3 N;
};

class hitable
{
public:
    virtual bool hit (const ray& r, float t_min, float t_max, record& rec) const = 0;
};

#endif
