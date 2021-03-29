#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <vector>

struct Color
{
  int r, g, b;
};

struct Size
{
  unsigned long width, height;
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

struct PatchSize
{
  double min_gap, max_gap;
  double min_to_max_ratio;
  double standard_deviation;
};

struct PatchSpikes
{
  double frequency;
  double threshold;
  double strength;
};

struct PatchEdge
{
  double distortion_frequency;
  double distortion_strength;
  double distortion_octaves;

  double roughness_frequency;
  double roughness_strength;
  double roughness_octaves;

  double roundness;
};

struct GiraffePatches
{
  PatchSize size;
  PatchEdge edge;
  PatchSpikes spikes;
};

struct PatternProperties
{
  Size size;
  double scale;
  GiraffeColors colors;
  GiraffePatches patches;
};

class GiraffeGenerator
{
public:
  virtual Color color_at(Point) const = 0;
};

class PointGenerator
{
public:
  virtual std::vector<Point> generate_points(size_t point_count) const = 0;
};

int area(Size);
double distance(Point, Point);

#endif
