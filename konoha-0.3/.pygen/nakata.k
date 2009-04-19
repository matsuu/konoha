using math.*;

WIDTH = 256
HEIGHT = 256

NSUBSAMPLES = 2
NAO_SAMPLES = 8

class Vec {
   double x;
   double y;
   double z;

   Vec(double x, double y, double z) {
       _x = x; _y = y; _z = z;
   }
}

double dot(Vec v0, Vec v1) {
   return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}


void cross(Vec v0, Vec v1, Vec v2) {
   v2.x = v0.y * v1.z - v0.z * v1.y;
   v2.y = v0.z * v1.x - v0.x * v1.z;
   v2.z = v0.x * v1.y - v0.y * v1.x;
}

void normalize(Vec v1) {
   double q = dot(v1, v1);
}
class RayIntersection {
   Vec rayPosition;
   Vec rayDirection;
   double distance;
   Vec    hitPosition;
   Vec    normal;
   Boolean    isHit;
}

class Sphere {
   Vec center;
   double radius;
   Sphere(double x, double y, double z, double r) {
       _center = new Vec(x, y, z);
       _radius = r;
   }

   void printing() {
       print _center, _radius
           }

}



Sphere[] spheres ;


void setupScene()
{
   spheres.add(new Sphere(1.0, 0.0, -2.2, 0.5));

   spheres[0].printing();
}

void run()
{
   int i;
   setupScene();
}

void main(String[] args) {
 spheres = new Sphere[0];


 run();
}

