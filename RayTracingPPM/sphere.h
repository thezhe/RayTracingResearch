#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable
{
public:
    //vars
    vec3 center;
    float radius;
    //constructors
    sphere() {}
    sphere (vec3 c, float r)
    {
        center = c;
        radius = r;
    }
    //inherited method
    bool hit (const ray& ray, float t_min, float t_max, record& rec) const override;
};

bool sphere::hit(const ray& ray, float t_min, float t_max, record& rec/*,bool SS*/) const
{
    vec3 co = ray.A - center;
    //sphere hit with respect to a parameter t on a ray
    float a = dot(ray.B,ray.B);
    float b = 2.0 * dot(co,ray.B);
    float c = dot(co,co) - radius*radius;
    float d = b*b-4*a*c;
    if (d>0)
    {
        //check both roots
        /*if (d<0.1){
        SS=true;
        }*/
        float t = (-b -sqrt(d))/(2*a);
        if(t<t_max && t>t_min)
        {
            rec.t = t;
            rec.p = ray.at_t(rec.t);
            rec.N= (rec.p - center)/radius;
            return true;
        }
        t = (-b +sqrt(d))/(2*a);
        if(t<t_max && t>t_min)
        {
            rec.t = t;
            rec.p = ray.at_t(rec.t);
            rec.N= (rec.p - center)/radius;
            return true;
        }
    }
    return false;
}
#endif
