// Basic point generator - Generates points based on rectangular grid
#ifndef BASIC_POINT_GENERATOR
#define BASIC_POINT_GENERATOR

#include "generator.hpp"

class BasicPointGenerator : public PointGenerator
{
  Size area_size;
  size_t attempts;
  PatchSize patch_size;

public:
  BasicPointGenerator(
      Size area_size, PatchSize patch_size, size_t attempts = 50)
  {
    this->area_size = area_size;
    this->patch_size = patch_size;
    this->attempts = attempts;
  }

  std::vector<Point> generate_points(size_t point_count) const override;

private:
  bool can_add_point(
      const std::vector<Point>& points, const std::vector<int>& radii,
      Point new_point, int min_radius) const;
};

#endif
