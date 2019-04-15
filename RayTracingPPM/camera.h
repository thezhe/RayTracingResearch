#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera
{
public:
//constants:
    vec3 lower_left;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
//constructor
    camera()
    {
        //embedding plane is z=-1
        lower_left = vec3(-2, -1, -1);
        horizontal = vec3(4,0,0);
        vertical = vec3 (0,2,0);
        origin = vec3 (0,0,0);
    }
//methods
    ray get_ray (float u, float v)
    {
        return ray (origin, lower_left + u*horizontal + v*vertical);
    }
};
#endif
