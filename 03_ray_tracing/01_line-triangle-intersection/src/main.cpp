/* 
  The equation of line in 3D is L = p0 + m*v0 

  Now the triangle in a plane is given by T = A + u(B-A) + v(C-A) 
  u >= 0, v >= 0 and u+v <= 1. 

  To find the intersection we put triangle = Line and then solve it. 
  In the paper "Fast, Minimum Storage Ray–Triangle Intersection"  by Tomas Möller and Ben Trumbore
  they have shown the following algorithm which is better then Cramer's rule. Well it is Cramer's rule but they are using a bit of tricks here and there. 

*/

#include <iostream>
#include <geometry_utility.h>

using namespace std;


//To check the intersection of a line(ray) and a triangle.
bool rayIntersectsTriangle(const Point &p0, const Vector &v0,
                           const Point &A, const Point &B, const Point &C)
{
  // Edges
  Vector E1(A, B);
  Vector E2(A, C);

  // Determinant
  Vector P = v0 ^ E2;
  double det = E1 * P;

  //0 determinant case, Ray is parallel
  if (det > -1e-9 && det < 1e-9)
    return false;  
  double invDet = 1.0 / det;

  // Vector from A to ray origin
  Vector T(A, p0);

  // Compute u
  double u = (T * P) * invDet;
  if (u < 0.0 || u > 1.0)
    return false;

  // Prepare to test v
  Vector Q = T ^ E1;

  double v = (v0 * Q) * invDet;
  if (v < 0.0 || u + v > 1.0)
    return false;

  // Compute t, but we don't need the value, just check ray direction
  double t = (E2 * Q) * invDet;
  if (t < 0.0)
    return false;  // Intersection is behind origin

  return true;     // HIT
}

int main() {
  Point p0(0,0,0);
  Vector v0(1,0,0);

  Point A(0,0,1), B(0,1,-1), C(0,-1,-1);

  if (rayIntersectsTriangle(p0, v0, A, B, C))
    cout << "It hits\n";
  else
    cout << "It misses\n";

  return 0;
}
