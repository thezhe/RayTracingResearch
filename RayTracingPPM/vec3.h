#include <math.h>
#include <iostream>

using namespace std;

class vec3 {
public:
//variables
float x,y,z;
//constructors
vec3() {}
vec3(float X, float Y, float Z) {x = X; y = Y; z = Z;}
//methods
float length() const {return sqrt(x*x+y*y+z*z);}
float length2() const {return x*x+y*y+z*z;}
};
//multiplying with constant
vec3 operator*(float t, const vec3 &v){
    return vec3(t*v.x,t*v.y,t*v.z);
}
vec3 operator*(const vec3 &v, float t){
    return vec3(t*v.x,t*v.y,t*v.z);
}
//element-wise multiplication
vec3 operator*(const vec3 &v1, const vec3 &v2){
return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
//dividing with constant
vec3 operator/(float t, const vec3 &v){
    return vec3(t/v.x,t/v.y,t/v.z);
}
vec3 operator/(const vec3 &v, float t){
    return vec3(v.x/t,v.y/t,v.z/t);
}
//adding with constant
vec3 operator+(float t, const vec3 &v){
    return vec3(t+v.x,t+v.y,t+v.z);
}
vec3 operator+(const vec3 &v, float t){
    return vec3(t+v.x,t+v.y,t+v.z);
}
//vector addition
vec3 operator+(const vec3 &v1, const vec3 &v2){
    return vec3(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
}
//vector subtraction
vec3 operator-(const vec3 &v1, const vec3 &v2){
    return vec3(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);
}
//dot product
float dot(const vec3 &v1, const vec3 &v2){
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}
//unit vector function
vec3 unit_vector (vec3 v){
return (v/v.length());
}

//random float between 0 and 1
float Frand()
{
    return ((float) rand())/(float)RAND_MAX;
}
//used for Matte/Lambertian material
vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p=2.0*vec3(Frand(),Frand(),Frand())-vec3(1,1,1);
    }
    while(p.length2()>=1.0);
    return p;
}
