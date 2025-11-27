
/*

  Algorithm
  1) Sort the points based on the x coordinate. If x coordinate is same then sort according to y. For both x and y the sorting is from smallest to largest. 
  2) Then add first 2 points of this sorted list the convexHull. Then add a third point which is non collinear to these first 2 points. 
  3) Then now loop over every point. Add every point to the hull and check if the last 3 points are taking a left turn. 
  Interlude:
  Well, how do we check if the last 3 points are making a left turn or not. This is done by taking the cross product of the vectors made by last 2 points(vector = v1) and 2nd last and 3rd last
  point(vector v2). 
  Take cross product. If the sign is positive then it is right turn, if the sign of the cross product is negative then it is a left turn. 

  4) If the last 3 points are making a left turn then remove the middle point. Do this iteratively. 
  This will give the upper hull. A simple test case is:

  vector<Point> inputPoints = {
    {0, 0},
    {1, 1},
    {2, 0},
    {3, 1}       
  };


*/



#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Point{
  double x, y;
};

struct Vector{
  Vector(const Point& b,  const Point& a) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
  double x, y;
};

double cross(Vector &a, Vector &b) {
  return a.x * b.y - a.y * b.x;
}

void printVector(vector<int>& vect) {
  if(vect.size() == 0) {
    cout << "EMPTY VECTOR" << endl;
    return;
  }
  for(int i = 0;i<vect.size();i++) {
    cout<<vect[i]<<endl;
  }
}

void checkLeftTurn(vector<Point> &convexHull) {
  if(convexHull.size() <= 3 ) return;

  int sz = convexHull.size()-1;

  Point p_last = convexHull[sz];
  Point p_sLast = convexHull[sz-1];
  Point p_tlast = convexHull[sz-2];

  Vector v2(p_last, p_sLast);
  Vector v1(p_sLast, p_tlast);

  double crossProd = cross(v2, v1);

  if(crossProd < 0) {
    convexHull.erase(convexHull.end() - 2);
    checkLeftTurn(convexHull);
  }
}

void saveConvexHull(vector<Point> &convexHull) {

  ofstream fout("convexHull.txt");

  for( auto &p: convexHull) {
    fout<<p.x << " "<< p.y <<endl;
  }

  fout.close();

}

int main() {

  // vector<Point> inputPoints = {
  //   {0, 0},
  //   {1, 1},
  //   {2, 0},
  //   {3, 1}       
  // };

  vector<Point> inputPoints = {
    {0, 0},
    {2, 1},
    {4, 0},
    {6, 2},
    {8, 0},

    {1, 3},
    {3, 4},
    {5, 5},
    {7, 4},
    {9, 3},

    {2, 2},
    {4, 3},
    {6, 3},
    {5, 1},
    {3, 2}
};


  int numPoints = inputPoints.size();
  vector<Point> convexHull;

  sort(inputPoints.begin(), inputPoints.end(), [](const Point &a, const Point &b){ 
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
  });

  for(auto &p:inputPoints) {
    cout<<p.x<<", "<<p.y<<endl;
  } 
    
  convexHull.push_back(inputPoints[0]);
  convexHull.push_back(inputPoints[1]);

  int k = 2;
  while(k<numPoints) {
    Vector v1(inputPoints[1], inputPoints[0]);
    Vector v2(inputPoints[k], inputPoints[0]);
    double crossProd = cross(v1, v2);
    if(crossProd != 0) break;
    k++;
  }

  convexHull.push_back(inputPoints[k]);

  cout<<"***********Initial Convex Hull***********"<<endl;
  for(int i = 0;i<convexHull.size();i++) {
    cout<<convexHull[i].x<<", "<<convexHull[i].y<<endl;
  }

  /*************************Incremnetal algorithm *************************/
  for(int i = k+1; i<inputPoints.size(); i++) {
    Point X = inputPoints[i];
    convexHull.push_back(X);
    checkLeftTurn(convexHull);    
  }

  cout<<"***********Final Convex Hull***********"<<endl;    
  for(int i = 0;i<convexHull.size();i++) {
    cout<<convexHull[i].x<<", "<<convexHull[i].y<<endl;
  }

  saveConvexHull(convexHull);

  return 0;
}
