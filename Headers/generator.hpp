// Interface that a generator should satisfy
#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <cmath>
#include <vector>

#include "geometry.hpp"

struct Color
{
  int r, g, b;
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
  double scale;
  double min_gap, max_gap;
  double min_to_max_ratio;
  double standard_deviation;
};

struct PatchSpikes
{
  int min_count;
  int max_count;

  double min_depth;
  double max_depth;

  double min_width;
  double max_width;
};

struct PatchEdge
{
  double distortion_frequency;
  double distortion_strength;
  double distortion_octaves;

  double roughness_frequency;
  double roughness_strength;
  double roughness_octaves;
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

#endif
