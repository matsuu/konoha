
class Vec {
  float x;
  float y;
  float z;
  Vec(double x, double y, double z) {
    _x = x; _y = y; _z = z;
  }
}

Vec[] v = new Vec[3];

class Vec2 {
  Vec v1;
  Vec2 () {
    _v1 = new Vec(0.1, 0.2, 0.3);
  }
  void f() {
    _v2;
  }
}
