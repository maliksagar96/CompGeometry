#pragma once

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
