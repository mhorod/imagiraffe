// Manipulations of 2D objects
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

struct Size
{
  unsigned long width, height;
};

struct Vector;

struct Point
{
  int x, y;
  Point(int x, int y)
  {
    this->x = x;
    this->y = y;
  }
  bool operator<(const Point& other) const
  {
    if (x < other.x) return true;
    if (x > other.x) return false;
    return y < other.y;
  }
};

struct Vector
{
  double x, y;
  Vector() : Vector(0, 0) {}
  Vector(double x, double y)
  {
    this->x = x;
    this->y = y;
  }
  Vector(Point p)
  {
    x = p.x;
    y = p.y;
  }
  Vector operator*(double m) const { return {m * x, m * y}; }
  Vector operator-(const Vector& other) const
  {
    return {x - other.x, y - other.y};
  }
  Vector operator+(const Vector& other) const
  {
    return {x + other.x, y + other.y};
  }
};

unsigned long area(Size);

double distance(Vector, Vector);
double dot(Vector, Vector);
double cross(Vector, Vector);
double length(Vector);
double angle_between(Vector, Vector);

double distance_from_bisector(Vector, Vector, Vector);
#endif
