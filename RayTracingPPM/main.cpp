//Zhe Deng U16716991
#include <fstream>
#include "hitablelist.h"
#include "sphere.h"
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
    int x = 200;
    int y = 100;
    file << "P3\n" << x << " " << y << "\n255\n";
    vec3 lower_left(-2, -1, -1);
    vec3 horizontal(4,0,0);
    vec3 vertical(0,2,0);
    vec3 origin(0,0,0);
    hitable *hlist[2];
    hlist[0] = new sphere(vec3(0,0,-1), 0.5);
    hlist[1] = new sphere(vec3(0,-100.5,-1),100);
    hitable *world = new hitablelist(hlist, 2);
    for (int j=y-1; j>-1; j--)  //from top row to bottom
    {
        for (int i = 0; i<x; i++)  //from left to right
        {
            float u =float(i)/float(x);
            float v = float(j)/float(y);
            ray ray (origin, lower_left + u*horizontal + v*vertical); //ray pos
            vec3 color = shader(ray, world); //associated color
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
