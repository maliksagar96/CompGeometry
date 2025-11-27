#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <geometry_utility.h>

using namespace std;

double dist(Point &a, Point &b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  double dz = a.z - b.z;
  return sqrt(dx*dx + dy*dy + dz*dz);
}

double bruteForce(vector<Point> &points, int left, int right) {
  double minDist = 1e9;
  for(int i = left; i <= right; i++) {
    for(int j = i + 1; j <= right; j++) {
      minDist = min(minDist, dist(points[i], points[j]));
    }
  }
  return minDist;
}

double stripDistance(vector<Point> &strip) {
  double minDist = 1e9;

  // brute force in strip is fine (strip is small)
  int n = strip.size();
  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      minDist = min(minDist, dist(strip[i], strip[j]));
    }
  }

  return minDist;
}

double divide_and_conquer(vector<Point> &points, int left, int right) {

  // small case
  if(right - left + 1 <= 3) {
    return bruteForce(points, left, right);
  }

  int mid = (left + right) / 2;
  double midX = points[mid].x;

  // left and right recursion (same vector, new indices)
  double dl = divide_and_conquer(points, left, mid);
  double dr = divide_and_conquer(points, mid + 1, right);

  double dmin = min(dl, dr);

  // build strip
  vector<Point> strip;
  for(int i = left; i <= right; i++) {
    if(fabs(points[i].x - midX) < dmin) {
      strip.push_back(points[i]);
    }
  }

  double dstrip = stripDistance(strip);
  return min(dmin, dstrip);
}

int main() {

  vector<Point> points = {
    { 0.2,  0.0,  0.0},
    { 7.8,  3.4, -2.0},
    {-4.2,  1.7,  3.3},
    { 0.0,  0.0,  0.0},
    { 1.1, -3.6,  2.2},
    {-2.5, -1.0, -4.4},
    { 5.9,  2.2,  1.1},
    {-3.3,  4.8, -0.9},
    { 2.0,  1.5,  3.7},
    { 6.4, -2.2,  0.4}
  };

  // sort by x
  sort(points.begin(), points.end(), [](Point &a, Point &b){
    if(a.x == b.x && a.y == b.y) return a.z < b.z;
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
  });

  double minDist = divide_and_conquer(points, 0, points.size() - 1);
  cout << "Minimum Distance = " << minDist << endl;

  return 0;
}
