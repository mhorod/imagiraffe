#include "basic_point_generator.hpp"

#include <cmath>
#include <random>
#include <set>
#include <utility>

Point random_point(std::pair<int, int> size)
{
  int x = rand() % size.first;
  int y = rand() % size.second;
  return {x, y};
}

int rand_in_range(int min, int max) { return rand() % (max - min + 1) + min; }

std::vector<Point> BasicPointGenerator::generate_points(
    size_t point_count) const
{
  double a = area(area_size);

  int chunk_size = sqrt(a / point_count);
  int max_radius = chunk_size * sqrt(2) / 2;
  int min_radius = sqrt(min_to_max_size_ratio) * max_radius;

  int max_chunk_x = area_size.width / chunk_size + 4;
  int max_chunk_y = area_size.height / chunk_size + 4;

  std::vector<int> radii;
  std::vector<Point> points;
  std::set<std::pair<int, int>> used_chunks;

  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::normal_distribution<> rand((min_radius + max_radius) / 2.0);

  for (int i = 0; i < point_count; i++)
  {
    auto chunk = random_point({max_chunk_x, max_chunk_y});
    for (int _ = 0; _ < attempts; _++)
    {
      chunk = random_point({max_chunk_x, max_chunk_y});
      if (!used_chunks.contains({chunk.x, chunk.y})) break;
    }

    chunk.x -= 2;
    chunk.y -= 2;
    for (int _ = 0; _ < attempts; _++)
    {
      auto point = random_point({chunk_size, chunk_size});
      point.x += chunk.x * chunk_size;
      point.y += chunk.y * chunk_size;
      if (can_add_point(points, radii, point, min_radius))
      {
        auto radius = rand(gen);
        used_chunks.insert({chunk.x, chunk.y});
        points.push_back(point);
        radii.push_back(radius);
        break;
      }
    }
  }
  return points;
}

bool BasicPointGenerator::can_add_point(
    const std::vector<Point>& points, const std::vector<int>& radii,
    Point new_point, int min_radius) const
{
  for (size_t i = 0; i < points.size(); i++)
    if (distance(new_point, points[i]) < radii[i]) return false;
  return true;
}
