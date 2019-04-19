#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material; //forward declaration

struct record
{
    float t; //t of hit location
    vec3 p;//hit location A+tB
    vec3 N;//hit point normal
    material *m;//hit material
};

class hitable
{
public:
    virtual bool hit (const ray& r, float t_min, float t_max, record& rec) const = 0; //declared in hitablelist
};

#endif
