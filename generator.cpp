#include "generator.hpp"

#include <cmath>

int area(Size s) { return s.width * s.height; }
double distance(Point p, Point q)
{
  int dx = p.x - q.x;
  int dy = p.y - q.y;
  return sqrt(dx * dx + dy * dy);
}
