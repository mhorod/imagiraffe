// Basic giraffe generator
// Very crude and could be improved, but does it job for simple giraffes
#ifndef BASIC_GIRAFFE_GENERATOR_HPP
#define BASIC_GIRAFFE_GENERATOR_HPP

#include <cmath>
#include <map>
#include <set>

#include "PerlinNoise.hpp"
#include "generator.hpp"

class BasicGiraffeGenerator : public GiraffeGenerator
{
  struct Spike
  {
    Vector origin;
    double width;
  };

  struct Patch
  {
    Point center;
    std::vector<Spike> spikes;
    std::set<Point> points;
    std::map<Point, Color> colors;
  };

  std::map<Point, size_t> patch_index;
  std::map<Point, size_t> second_closest_index;

  PatternProperties properties;
  const PointGenerator& point_generator;
  std::vector<Point> patch_points;
  std::vector<Patch> patches;
  const siv::PerlinNoise noise;

public:
  BasicGiraffeGenerator(
      PatternProperties properties, const PointGenerator& point_generator);

  Color color_at(Point p) const override;

private:
  std::vector<Point> generate_points(
      const PatternProperties& properties, const PointGenerator& generator);
  std::vector<Patch> generate_patches();

  Patch colored_patch(Patch) const;
  Patch spiked_patch(Patch) const;
  Spike generate_spike(Vector begin, Vector end) const;
  Color patch_color_at(Vector, const Patch&) const;

  double secondary_tint_at(Vector) const;
  double edge_distortion_at(Vector point, Point patch_center) const;
  double gap_between_patches(Point, Point) const;

  bool inside_patch(const Patch&, Vector) const;
  bool inside_spike(const Patch& patch, const Spike&, Vector) const;

  Color shade_at(Vector, Color) const;
};

#endif
