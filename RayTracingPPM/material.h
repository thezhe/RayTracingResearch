#ifndef MATERIALH
#define MATERIALH

#include "hitable.h"

class material
{
public:
    virtual bool scatter (const ray& r, const record& rec, vec3& attenuation, ray& scattered) const = 0;
};
bool refract (const vec3& v, const vec3& N, float ri, vec3& refracted)
{
    vec3 unit_v=unit_vector(v);
    float dt = dot (unit_v, N);
    float d = 1.0 - ri*ri*(1-dt*dt);
    if (d>0)
    {
        refracted = ri*(unit_v-N*dt) - N*sqrt(d);
        return true;
    }
    else
        return false;
}
vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2*dot(v,n)*n;
}
float schlick (float cosine, float ri)
{
    float r0 = (1-ri)/(1+ri);
    r0 = r0*r0;
    return r0 +(1-r0)*pow((1-cosine),5);
}
/*
*************
diffuse/matte
*************
*/
class lambertian: public material
{
public:
    //vars
    vec3 albedo;
    //constructors
    lambertian(const vec3& a)
    {
        albedo = a;
    }
    //inherited methods
    bool scatter (const ray& r, const record& rec, vec3& attenuation, ray& scattered) const override;
};

bool lambertian::scatter(const ray& r, const record& rec, vec3& attenuation, ray& scattered) const
{
    vec3 target = rec.p + rec.N + random_in_unit_sphere();
    scattered = ray(rec.p, target-rec.p);
    attenuation = albedo;
    return true;
}
/*
******
metals
******
*/
class metal: public material
{
public:
    //vars
    vec3 albedo;
    float fuzz; //adds lambertian randomization at end of direction vector
    //constructors
    metal(const vec3& a, float f)
    {
        albedo = a;
        if (f<1 && f>=0)
        {
            fuzz=f;
        }
        else
        {
            fuzz =1;
        }
    }
    //inherited methods
    bool scatter (const ray& r, const record& rec, vec3& attenuation, ray& scattered) const override;

};
bool metal::scatter(const ray& r, const record& rec, vec3& attenuation, ray& scattered) const
{
    vec3 direction = unit_vector(r.B);
    vec3 reflected =  reflect(direction, rec.N);
    scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.B, rec.N)>0);
}
/*
***********
dielectrics
***********
*/
class dielectric: public material
{
    public:
    //vars
    float ref_idx;
    //constructors
    dielectric(float ri)
    {
        ref_idx = ri;
    }
    //inherited methods
    bool scatter (const ray& r, const record& rec, vec3& attenuation, ray& scattered) const override;
};

bool dielectric::scatter(const ray& r, const record& rec, vec3& attenuation, ray& scattered) const
{
    vec3 normal = rec.N;
    vec3 reflected = reflect (r.B, rec.N);
    attenuation = vec3(1,1,1);
    float ri = ref_idx;
    vec3 refracted;
    float reflect_prob = 1.0;
    float cosine =ref_idx * dot(r.B, rec.N) / r.B.length();
    if (dot(r.B, rec.N)>0)
    {
        normal = -1*normal;
    }
    else
    {
        ri = 1/ri;
        cosine = -1*cosine;
    }
    if (refract(r.B,normal,ri,refracted))
    {
        reflect_prob = schlick(cosine, ref_idx);
    } else {
    scattered = ray(rec.p, reflected);
    }
    if (Frand()<reflect_prob){
        scattered = ray(rec.p, reflected);
    }
    else {
    scattered = ray(rec.p, refracted);
    }
    return true;
}
#endif
