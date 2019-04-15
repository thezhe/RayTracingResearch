#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitablelist: public hitable{
    public:
        //vars
        hitable **hlist; //*array[# spheres/shapes]
        int lsize;
        //constructors
        hitablelist (){}
        hitablelist(hitable **l, int n) {hlist=l; lsize = n;}
        //inherited methods
        bool hit(const ray& ray, float t_min, float t_max, record& rec) const override;
};

bool hitablelist::hit(const ray& ray, float t_min, float t_max, record& rec) const{
    record temp_rec;
    bool hit_anything = false;
    double closest_p = t_max;
    for (int i = 0; i<lsize; i++){
        //hlist[i] -> hit references the declaration from "sphere.h"
        if(hlist[i]->hit (ray, t_min, closest_p, temp_rec)){
            hit_anything = true;
            closest_p=temp_rec.t;
            rec=temp_rec;
        }
    }
    return hit_anything;
}
#endif
