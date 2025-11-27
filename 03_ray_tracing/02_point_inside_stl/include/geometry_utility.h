#pragma once

#include <iostream>

struct Point {
  Point(double x, double y, double z) : x(x), y(y), z(z) {}

  double x, y, z;

  // Point + Point
  Point operator+(const Point &p) const {
    return Point(x + p.x, y + p.y, z + p.z);
  }

  // Point - Point
  Point operator-(const Point &p) const {
    return Point(x - p.x, y - p.y, z - p.z);
  }

  // Point * scalar
  Point operator*(double s) const {
    return Point(s * x, s * y, s * z);
  }

  // Point / scalar
  Point operator/(double s) const {
    return Point(x / s, y / s, z / s);
  }

};

//To print the Point object using the cout.
std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
  return os;
}

struct Vector {
  Vector(Point p, Point q)
    : x(q.x - p.x), y(q.y - p.y), z(q.z - p.z) {}

  Vector(double x, double y, double z)
    : x(x), y(y), z(z) {}

  double x, y, z;

  double getMagnitude() const {
    return (x*x + y*y + z*z);
  }

  // Vector cross product
  Vector operator^(const Vector &b) const {
    return Vector(
      y * b.z - z * b.y,
      z * b.x - x * b.z,
      x * b.y - y * b.x
    );
  }

  // Dot product
  double operator*(const Vector &b) const {
    return x * b.x + y * b.y + z * b.z;
  }

  // Vector + Vector
  Vector operator+(const Vector &b) const {
    return Vector(x + b.x, y + b.y, z + b.z);
  }

  // Vector - Vector
  Vector operator-(const Vector &b) const {
    return Vector(x - b.x, y - b.y, z - b.z);
  }

  // Vector * scalar
  Vector operator*(double s) const {
    return Vector(s * x, s * y, s * z);
  }

  // Vector / scalar
  Vector operator/(double s) const {
    return Vector(x / s, y / s, z / s);
  }
};

//To print the Vector object using the cout.
std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

//To check the intersection of a line(ray) and a triangle. Returns true if the ray and triangle intersects.
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