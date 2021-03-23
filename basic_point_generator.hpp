#ifndef BASIC_POINT_GENERATOR
#define BASIC_POINT_GENERATOR

#include "generator.hpp"

class BasicPointGenerator : public PointGenerator
{
  Size area_size;
  size_t attempts;
  double min_to_max_size_ratio;

public:
  BasicPointGenerator(
      Size area_size, double min_to_max_size_ratio, size_t attempts = 50)
  {
    this->area_size = area_size;
    this->min_to_max_size_ratio = min_to_max_size_ratio;
    this->attempts = attempts;
  }

  std::vector<Point> generate_points(size_t point_count) const override;
  bool can_add_point(
      const std::vector<Point>& points, const std::vector<int>& radii,
      Point new_point, int min_radius) const;
};

#endif
