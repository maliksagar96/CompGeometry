/*
  Well if one has 4 points lets say P, Q , R and S. There are 2 lines PQ and RS. 
  To check if the line segments intersect or not we can implement the logic the points R and S shoudl lie on the different sides of the line PQ and 
  the points PQ should lie on the different sides of the line RS.
  This could be checked by cross products. There is another method to check the intersections.

  Then there is the second method which is doing the same thing as the first method but is less visible the way it is written. That's why I have written both the methods for clarity. 
*/

/*

This was such an amazing problem from the domain of computational geometry. It was genuinely enjoyable to solve, and there was a lot to learn along the way.

First, the time complexity.
We are given several line segments and must determine which ones intersect.
The brute-force approach, which I demonstrated in the first file, checks every pair of segments. This leads to a time complexity of roughly n², since every segment is tested against every other one.

The sweep-line algorithm is far more efficient. Its overall time complexity is composed of two parts:
• sorting all events, which takes n log n, and
• handling each intersection, which takes k log n, where k is the number of intersections found.

The k log n term appears because every time an intersection is detected, the algorithm updates a balanced tree (in C++, this is implemented using std::set). Each insertion, deletion, or lookup in this tree costs log n, so k such operations give k log n.

One of the nicest discoveries in this problem was how useful a set is. A set in C++ is actually a balanced binary search tree that automatically rearranges itself to stay efficient. This property makes it perfect for maintaining the active list of segments during a sweep.

Another pleasant surprise was learning that even custom structs can be stored in a set. By defining how two structs should be compared, the set can order and manage them just like built-in types. Hash maps and hash sets can also support structs with a bit more setup—something to explore later.

Overall, although this problem leans strongly toward mathematics, turning that mathematical idea into an optimal computational solution takes both understanding and programming skill. C++ really shines in problems like these, and solving them shows just how powerful the language can be.

Computational geometry is awesome!

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

struct Point {
  double x, y;
};

struct Segment {
  Point p, q;
};

struct Vector {
  double x, y;
  Vector(Point b, Point a) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
};

struct Event {
  Event(Point p, bool isLeft, int id) : p(p), isLeft(isLeft), id(id) {}
  Point p;
  bool isLeft;
  int id;

  bool operator<(const Event &e) const{
    if(p.y == e.p.y) 
      return p.x < e.p.x;
    return p.y < e.p.y;
  }

};

struct Result {

  Result(int index1, int index2, Point intersectionPoint):index1(index1), index2(index2), intersectionPoint(intersectionPoint) {}
  Point intersectionPoint;
  int index1, index2;

  bool operator<(const Result& other) const {
    int a1 = std::min(index1, index2);
    int b1 = std::max(index1, index2);

    int a2 = std::min(other.index1, other.index2);
    int b2 = std::max(other.index1, other.index2);

    if (a1 != a2) return a1 < a2;
    return b1 < b2;
}


  

};

double cross(const Vector &A, const Vector &B) {
  return A.x * B.y - A.y * B.x;  // considering magnitude only.
}


int orientation(const Point &a, const Point &b, const Point &c) {
    double val = cross(Vector(b, a), Vector(c, a)); // (b-a) x (c-a)
    const double EPS = 1e-9;
    if (fabs(val) < EPS) return 0;
    return (val > 0) ? 1 : 2;
}

//Not considering and collinear cases.
bool checkIntersection(Segment &s1, Segment &s2) {

  int o1 = orientation(s1.p, s1.q, s2.p);
  int o2 = orientation(s1.p, s1.q, s2.q);
  int o3 = orientation(s2.p, s2.q, s1.p);
  int o4 = orientation(s2.p, s2.q, s1.q);

  if((o1 != o2) && (o3 != o4)) 
    return true;

  return false;
}


bool checkIntersection(const Segment &s1, const Segment &s2, Point &I) {
  Vector r(s1.q, s1.p);
  Vector s(s2.q, s2.p);

  Vector qp(s2.p, s1.p);

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



void isIntersect(vector<Segment> &lines) {

  vector<Event> events;
  set<Result> results;


  for(int i=0;i<lines.size();i++) {
    if(lines[i].p.x < lines[i].q.x) {
      events.push_back(Event(lines[i].p, true, i));
      events.push_back(Event(lines[i].q, false, i));
    }
    else {
      events.push_back(Event(lines[i].p, false, i));
      events.push_back(Event(lines[i].q, true, i));
    }
    
  }

  sort(events.begin(), events.end(), [](Event &a, Event &b) {
                                        return (a.p.x < b.p.x);});

  set<Event> active;

  for(int i = 0;i<events.size();i++) {
    Event curr = events[i];
    int index = curr.id;
    Point intersectionPoint;

    //if the current point is a left point
    if(curr.isLeft) {

      //find next neighbour
      auto next = active.lower_bound(curr);
      
      //find previous neighbour
      auto prev = (next == active.begin() ? active.end() : std::prev(next));  

      //check if the prev neighbour intersects
      if(prev != active.end() && checkIntersection(lines[index], lines[prev->id], intersectionPoint)) {        
        results.insert(Result(index, prev->id, intersectionPoint));
      }

      //check if the next neighbour intersects
      if(next != active.end() && checkIntersection(lines[index], lines[next->id])) {
        results.insert(Result(index, next->id, intersectionPoint));
      }

      active.insert(curr);
    }

    //if the current point is a right point
    else{

      //If we have detected a right point then there must be a left point assosicated with this right point. We first find that.
      Event leftEvent(lines[index].p, true, index);
      auto it = active.find(leftEvent);
      
      //find next neighbour of this leftevent
      auto next = std::next(it);
      
      //find previous neighbour of this leftevent.
      auto prev = (it == active.begin()? active.end() : std::prev(it));
      
      if(prev != active.end() && checkIntersection(lines[index], lines[prev->id])) {        
        results.insert(Result(index, prev->id, intersectionPoint));  
      }

      //check if the next neighbour intersects
      if(next != active.end() && checkIntersection(lines[index], lines[next->id])) {
        results.insert(Result(index, next->id, intersectionPoint));
      }

      active.erase(it);
    }

  }

  for(auto result:results) {
    cout<<"The index of intersecting lines = "<<result.index1+1<<" and "<<result.index2+1<<endl;
    cout<<"The intersection point = "<<result.intersectionPoint.x+1<<", "<<result.intersectionPoint.y+1<<endl;
  }

}


int main() {
  vector<Segment> lines = {
        { {1, 5}, {4, 5} },
        { {2, 5}, {10, 1} },
        { {3, 2}, {10, 3} },
        { {6, 4}, {9, 4} },
        { {7, 1}, {8, 1} }
    };

  isIntersect(lines);

  return 0;
}
