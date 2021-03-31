#include "geometry.hpp"

#include <cmath>

unsigned long area(Size s) { return s.width * s.height; }

double distance(Vector a, Vector b)
{
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - b.x * a.y; }
double length(Vector v) { return sqrt(v.x * v.x + v.y * v.y); }
double angle_between(Vector a, Vector b)
{
  return acos(dot(a, b) / (length(a) * length(b)));
}

// Calculates the distance of p from bisector of ab
double distance_from_bisector(Vector a, Vector b, Vector p)
{
  auto d1 = distance(a, p);
  auto d2 = distance(b, p);
  auto d = distance(a, b);

  double v = d1 * d1 - d2 * d2;
  return fabs(v / (2 * d));
}
