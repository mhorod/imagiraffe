#ifndef BASIC_GIRAFFE_GENERATOR_HPP
#define BASIC_GIRAFFE_GENERATOR_HPP

#include <cmath>

#include "PerlinNoise/PerlinNoise.hpp"
#include "generator.hpp"

class BasicGiraffeGenerator : public GiraffeGenerator
{
  PatternProperties properties;
  const PointGenerator& point_generator;
  const std::vector<Point> patch_points;
  const siv::PerlinNoise patch_distortion_noise;
  const siv::PerlinNoise patch_roughness_noise;
  const siv::PerlinNoise secondary_tint_noise;
  const siv::PerlinNoise shade_noise;

public:
  BasicGiraffeGenerator(
      PatternProperties properties, const PointGenerator& point_generator)
      : point_generator(point_generator),
        patch_roughness_noise(rand()),
        patch_distortion_noise(rand()),
        secondary_tint_noise(rand()),
        shade_noise(rand()),
        patch_points(generate_points(properties, point_generator))
  {
    this->properties = properties;
  }

  std::vector<Point> generate_points(
      const PatternProperties& properties, const PointGenerator& generator);

  Color color_at(Point p) const override;

private:
  double patch_distortion_at(Point) const;
  double secondary_tint_at(Point) const;
  double patch_roughness_at(Point) const;
  double edge_distortion_at(Point point, Point patch_center) const;
  double gap_between_points(Point, Point) const;
  Color shade_at(Point, Color) const;
};

#endif
