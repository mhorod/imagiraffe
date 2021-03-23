#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <vector>

struct Color
{
  int r, g, b;
};

struct Size
{
  unsigned width, height;
};

struct Point
{
  int x, y;
};

struct GiraffeColors
{
  Color patch;
  Color gap;
  Color middle_tint;
  Color secondary_tint;
};

struct GiraffePatches
{
  int gap_size;

  double min_to_max_size_ratio;

  double patch_distortion_frequency;
  double patch_distortion_strength;

  double patch_roughness;

  double rounded_corners_strength;
};

class GiraffeGenerator
{
public:
  virtual Color color_at(Point) const = 0;
};

struct PatternProperties
{
  Size size;
  double scale;
  GiraffeColors colors;
  GiraffePatches patches;
};

class PointGenerator
{
public:
  virtual std::vector<Point> generate_points(size_t point_count) const = 0;
};

int area(Size);
double distance(Point, Point);

#endif
