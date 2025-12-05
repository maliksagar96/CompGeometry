/*
  We want to find the intersection point of two line segments in 2D.
  The first segment goes from point P to point Q.
  The second segment goes from point R to point S.

  A line in vector/parametric form is written as:
      L = P + tV
  where:
      P = starting point
      V = direction vector
      t = parameter (moves along the line)

  For segment PQ:
      direction V1 = (Q - P)
      So the parametric form is:
          L1(t) = P + t(Q - P)          (1)

  For segment RS:
      direction V2 = (S - R)
      So the parametric form is:
          L2(u) = R + u(S - R)          (2)

  If the two segments intersect, then both parametric equations must
  reach the *same point* at the same time. So we set:
          L1(t) = L2(u)                 (3)

  We now solve (1), (2), and (3) for t and u.
  This is just solving two linear equations from basic class-12 algebra.

  IMPORTANT:
      For an infinite line, t and u can be anything.
      But for a *segment*, we must restrict:
          0 <= t <= 1
          0 <= u <= 1

      This means:
        - t = 0 gives point P
        - t = 1 gives point Q
        - values between 0 and 1 stay inside the segment PQ
      Same logic for u on segment RS.

  Once we find t (and u) inside the range [0,1],
  we compute the actual intersection point using:
          Intersection = P + t(Q - P)

  That is the point where the two segments cross.
*/



#include <iostream>
#include <vector>
using namespace std;

struct Point {
  double x, y;
};

struct Segment {
  Point p, q;
};

struct Vector {
  double x, y;
  Vector(Point a, Point b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
};

double cross(const Vector &A, const Vector &B) {
  return A.x * B.y - A.y * B.x;  // considering magnitude only.
}

bool intersect(const Segment &s1, const Segment &s2, Point &I) {
  Vector r(s1.p, s1.q);
  Vector s(s2.p, s2.q);

  Vector qp(s1.p, s2.p);

  double denom = cross(r, s);
  if (denom == 0) return false; 

  double t = cross(qp, s) / denom;
  double u = cross(qp, r) / denom;

  if (t < 0 || t > 1) return false;
  if (u < 0 || u > 1) return false;

  I.x = s1.p.x + t * r.x;
  I.y = s1.p.y + t * r.y;
  return true;
}

int main() {
  vector<Segment> lines = {
    {{0,0}, {4,4}},
    {{0,1}, {1,0}}
    
  };

  for (int i = 0; i < lines.size(); i++) {
    for (int j = i+1; j < lines.size(); j++) {

      Point I;
      if (intersect(lines[i], lines[j], I)) {
        cout << "Segments " << i << " & " << j
             << " intersect at (" << I.x << ", " << I.y << ")\n";
      }
    }
  }

  return 0;
}
