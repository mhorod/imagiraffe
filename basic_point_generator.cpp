#include "basic_point_generator.hpp"

#include <cmath>
#include <iostream>
#include <random>
#include <set>
#include <utility>

Point random_point(std::pair<int, int> size)
{
  int x = rand() % size.first;
  int y = rand() % size.second;
  return {x, y};
}

int get_chunk_size(int area, int point_count)
{
  return sqrt(static_cast<double>(area) / point_count);
}

// Return minimum and maximum radius of patch circle, based on chunk size and
// given ratio
std::pair<int, int> get_radii_bound(
    int chunk_size, double min_to_max_size_ratio)
{
  int max_radius = chunk_size / (1 + sqrt(min_to_max_size_ratio));
  int min_radius = sqrt(min_to_max_size_ratio) * max_radius;
  return {min_radius, max_radius};
}

// Returns generated points
// point_count is an approximation of how many of returned points should
// be present inside given area
std::vector<Point> BasicPointGenerator::generate_points(
    size_t point_count) const
{
  int chunk_size = get_chunk_size(area(area_size), point_count);
  auto radii_bound = get_radii_bound(chunk_size, patch_size.min_to_max_ratio);

  int chunk_border = 1;  // How many extra chunks around the area
  int chunks_x = area_size.width / chunk_size + 2 * chunk_border;
  int chunks_y = area_size.height / chunk_size + 2 * chunk_border;
  point_count = chunks_x * chunks_y;

  std::vector<int> radii;
  std::vector<Point> points;

  std::set<std::pair<int, int>> free_chunks;
  for (int x = -chunk_border; x <= chunks_y - chunk_border; x++)
    for (int y = -chunk_border; y <= chunks_x - chunk_border; y++)
      free_chunks.insert({x, y});

  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::normal_distribution<> rnd(
      (radii_bound.first + radii_bound.second) / 2.0,
      patch_size.standard_deviation);

  for (int i = 0; i < point_count; i++)
  {
    // Stop if there are no free chunks
    if (free_chunks.size() == 0) return points;

    // Randomly choose a chunk without a point
    auto it = std::next(free_chunks.begin(), gen() % free_chunks.size());
    Point chunk = {it->first, it->second};

    for (int _ = 0; _ < attempts; _++)
    {
      // Choose random point in the middle of the chunk
      auto point = random_point({chunk_size / 2, chunk_size / 2});
      point.x += chunk.x * chunk_size;
      point.y += chunk.y * chunk_size;
      auto radius = rnd(gen);
      if (can_add_point(points, radii, point, radius))
      {
        points.push_back(point);
        radii.push_back(radius);
        break;
      }
    }

    // Don't try this chunk again
    free_chunks.erase({chunk.x, chunk.y});
  }

  return points;
}

// Checks whether given point with radius can be added to existing ones
bool BasicPointGenerator::can_add_point(
    const std::vector<Point>& points, const std::vector<int>& radii,
    Point new_point, int radius) const
{
  if (points.size() == 0) return true;
  for (size_t i = 0; i < points.size(); i++)
    if (distance(new_point, points[i]) < radii[i] + radius) return false;
  return true;
}
