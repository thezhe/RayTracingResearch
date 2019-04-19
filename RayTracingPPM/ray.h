#ifndef RAYH
#define RAYH

#include "vec3.h"

using namespace std;

class ray
{
public:
//vars for ray AB
    vec3 A;//origin
    vec3 B;//direction
//constructors
    ray() {}
    ray (const vec3& a, const vec3& b)
    {
        A=a;
        B=b;
    }
//methods
    vec3 at_t(float t) const
    {
        return A + t*B;
    }
};


#endif
