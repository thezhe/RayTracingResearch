//Zhe Deng U16716991
#include <fstream>
#include <time.h>
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"
#include "float.h"

using namespace std;

//random float between 0 and 1
float Frand()
{
    return ((float) rand())/(float)RAND_MAX;
}
//used for Matte objects
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

//determines pixel color
vec3 shader(const ray& r, hitable *world)
{
    record rec;
    if (world->hit(r, 0.001, FLT_MAX,rec)) //t_min>0 to solve float errors
    {
        vec3 target=rec.p + rec.N + random_in_unit_sphere();
        return 0.5*shader(ray(rec.p, target-rec.p), world); //avg b/w normal and white
        //return 0.5*(rec.N+1);
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
    int samples = 16; //16 times super sampling
    file << "P3\n" << x << " " << y << "\n255\n";
    hitable *hlist[2];
    hlist[0] = new sphere(vec3(0,0,-1), 0.5);
    hlist[1] = new sphere(vec3(0,-100.5,-1),100);
    hitable *world = new hitablelist(hlist, 2);
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
                color = color + shader(Sample, world); //associated color
            }
            color = color/float(samples);
            color = vec3(sqrt(color.x),sqrt(color.y),sqrt(color.z)); //gamma correction
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
//TODO super sampling for edges only
