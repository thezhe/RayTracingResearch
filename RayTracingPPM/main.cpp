//Zhe Deng U16716991
#include <fstream>
#include <time.h>
#include "float.h"
#include "camera.h"
#include "sphere.h"
#include "hitablelist.h"
#include "material.h"

using namespace std;

//determines pixel color
vec3 shader(const ray& r, hitable *world, int depth)
{
    record rec;
    if (world->hit(r, 0.001, FLT_MAX,rec)) //t_min>0 to solve float errors
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.m->scatter(r,rec,attenuation,scattered)){
            return attenuation*shader(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else  //background
    {
        vec3 unit = unit_vector(r.B);
        float t = 0.5*(unit.y+1); //max is t 1.707/2 when ray.B is at (0,1,-1)
        return (1-t)*vec3(1,1,1) + t*vec3(0.5,0.7,1); //white to blue
    }
}
//driver code
int main()
{
    srand(time(0));
    ofstream file;
    file.open("RayTracing.ppm");
    int x = 2000;
    int y = 1000;
    int samples = 16; //16 times for testing, >200 for convergence
    file << "P3\n" << x << " " << y << "\n255\n";
    hitable *hlist[4];
    hlist[0] = new sphere(vec3(0,-0.25,-1), 0.25, new lambertian(vec3(0.3, 0.0, 0.1)));
    hlist[1] = new sphere(vec3(0,-100.5,-1),100, new lambertian (vec3(0.3, 0.3, 0.5)));
    hlist[2] = new sphere(vec3(0.5,-0.25,-1),0.25, new metal (vec3(0.2, 0.7, 0.2),0.25));
    hlist[3] = new sphere(vec3(-0.5,-0.25,-1),0.25, new dielectric(1.5));
    hitable *world = new hitablelist(hlist, 4);
    camera cam;
    for (int j=y-1; j>-1; j--)  //from top row to bottom
    {
        for (int i = 0; i<x; i++)  //from left to right
        {
            //with SS
            vec3 color(0,0,0);
            for (int s=0; s<samples; s++)
            {
                float u = float(i + Frand())/float(x);
                float v = float(j + Frand())/float(y);
                ray Sample = cam.get_ray(u,v);
                color = color + shader(Sample, world, 0); //associated color
            }
            color = color/float(samples);
            color = vec3(sqrt(color.x),sqrt(color.y),sqrt(color.z)); //gamma correction (power = 1/gamma)
            color = 255.99*color;
            int r = int(color.x);
            int g = int(color.y);
            int b = int(color.z);
            file << r << " " << g << " " << b << "\n"; //rgb per pixel
        }
    }
    file.close();
    cout << "Done" << endl;
    return 0;
}
//TODO state downside SS needed for convergence to gorund truth
//TODO random in sphere optimize downward weighted Frand vec3
//TODO more material types?
