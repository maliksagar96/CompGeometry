/* 
  Using the ray and triangle interaction we can find if a given point is inside the geometry represented by triangles, such as VTK or STL.
  We can take the point and send a ray from it in only single direction. If it cuts the triangles odd number of times then it is inside. 
  If it cuts the triangles even number of times then it is outisde the geometry.
*/

#include <iostream>
#include <geometry_utility.h>
#include <VTKReader.h>
#include <memory>

using namespace std;

int main() {

  string filename = "../src/sphere.vtk";

  VTKReader sphere(filename);
  
	sphere.loadPoints();
	sphere.loadConnectivity();

  vector<double> vertices = sphere.getPoints();
  vector<int> connectivity = sphere.getConnectivity();  
  vector<vector<Point>> triangles;
  int numCells = sphere.getNumCells();

  for (int i = 0; i < connectivity.size(); i += 3) {
    int i0 = connectivity[i];
    int i1 = connectivity[i+1];
    int i2 = connectivity[i+2];

    Point p0(
      vertices[3*i0], vertices[3*i0 + 1], vertices[3*i0 + 2]
    );

    Point p1(
      vertices[3*i1], vertices[3*i1 + 1], vertices[3*i1 + 2]
    );

    Point p2(
      vertices[3*i2], vertices[3*i2 + 1], vertices[3*i2 + 2]
    );

    triangles.push_back({p0, p1, p2});
  }

  Point testPoint(1.25, 0.25, 0.25);
  Vector rayDirection(1,0,0);

  int counter = 0;
  for(int i = 0;i<triangles.size();i++) {
    if(rayIntersectsTriangle(testPoint, rayDirection, triangles[i][0], triangles[i][1], triangles[i][2]))
      counter++;
  }

  if(counter % 2 == 0) {
    cout<<"The given point is OUTSIDE the sphere.\n";
  }

  else {
    cout<<"The given point is INSIDE the sphere.\n";
  }

  return 0;
}
