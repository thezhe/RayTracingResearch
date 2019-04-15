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
}//dividing with constant
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
