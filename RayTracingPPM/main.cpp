//Zhe Deng U16716991
#include <fstream>
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"
#include "float.h"

using namespace std;

vec3 shader(const ray& ray, hitable *world) //determines pixel color
{
    record rec;
    if (world->hit(ray, 0.0, MAXFLOAT,rec))
    {
        return 0.5*vec3(rec.N+1); //avg b/w normal and white
    }
    else  //background
    {
        vec3 unit = unit_vector(ray.B);
        float t = 0.5*(unit.y+1); //max is 1.707/2
        return (1-t)*vec3(1,1,1) + t*vec3(0.5,0.7,1); //white to blue
    }
}

int main()
{
    ofstream file;
    file.open("RayTracing.ppm");
    int x = 2000;
    int y = 1000;
    int samples = 4;
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
            vec3 color(0,0,0);
            for (int s=0; s<samples; s++)
            {
                float u =float(i+drand48())/float(x);
                float v = float(j+drand48())/float(y);
                ray ray =  cam.get_ray(u,v);
                color = color + shader(ray, world); //associated color
            }
            color = color/float(samples);
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
