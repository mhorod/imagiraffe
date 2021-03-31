#include "basic_giraffe_generator.hpp"

#include <cmath>
#include <iostream>

const int DEFAULT_PATCH_COUNT = 40;
double logistic(double x) { return 1 / (1 + pow((0.75 - x) / x, 2)); }

BasicGiraffeGenerator::BasicGiraffeGenerator(
    PatternProperties properties, const PointGenerator& point_generator)
    : point_generator(point_generator), noise(rand())
{
  this->properties = properties;
  patch_points = generate_points(properties, point_generator);
  patches = generate_patches();
  for (size_t i = 0; i < patches.size(); i++)
    for (auto p : patches[i].points) patch_index[p] = i;
}

std::vector<size_t> indices_by_distance(
    const std::vector<Point>& points, Point p)
{
  std::vector<std::pair<double, size_t>> d(points.size());
  for (size_t i = 0; i < points.size(); i++) d[i] = {distance(points[i], p), i};
  sort(d.begin(), d.end());
  std::vector<size_t> result(points.size());
  for (size_t i = 0; i < points.size(); i++) result[i] = d[i].second;
  return result;
}

// Organizes points into patches
std::vector<BasicGiraffeGenerator::Patch>
BasicGiraffeGenerator::generate_patches()
{
  std::vector<Patch> patches;
  for (auto p : patch_points) patches.push_back({p, {}});

  for (size_t x = 0; x < properties.size.width; x++)
    for (size_t y = 0; y < properties.size.height; y++)
    {
      Point p(x, y);
      auto indices = indices_by_distance(patch_points, p);
      second_closest_index[p] = indices[1];
      patch_index[p] = indices[0];
      patches[indices[0]].points.insert(p);
    }

  for (auto& p : patches) p = spiked_patch(std::move(p));
  for (auto& p : patches) p = colored_patch(std::move(p));
  return patches;
}

BasicGiraffeGenerator::Patch BasicGiraffeGenerator::spiked_patch(
    Patch patch) const
{
  std::default_random_engine rd;
  rd.seed(rand() * patch.center.x * patch.center.y);
  std::mt19937 gen(rd());

  std::uniform_real_distribution<> dis(0, 1);

  int spike_count = properties.patches.spikes.min_count +
                    rand() % (properties.patches.spikes.max_count -
                              properties.patches.spikes.min_count + 1);

  double a = 2 * M_PI / spike_count;
  double off = dis(rd) * M_PI;
  double scale = sqrt(properties.scale);
  for (int i = 0; i < spike_count; i++)
  {
    Spike spike;

    double position_angle = off + a * i + dis(gen) * 0.2 - 0.1;
    double dx = cos(position_angle);
    double dy = sin(position_angle);
    double x = patch.center.x;
    double y = patch.center.y;
    while (true)
    {
      Point p = {static_cast<int>(x), static_cast<int>(y)};
      if (!patch.points.contains(p)) break;
      x += dx;
      y += dy;
    }
    double dst = distance(patch.center, {x, y});

    double depth = dis(gen) * (properties.patches.spikes.max_depth -
                               properties.patches.spikes.min_depth) +
                   properties.patches.spikes.min_depth;
    double width = dis(gen) * (properties.patches.spikes.max_width -
                               properties.patches.spikes.min_width) +
                   properties.patches.spikes.min_width;

    depth += properties.patches.size.min_gap;
    depth *= scale;
    depth = fmin(depth, dst);

    Vector origin = {x - dx * depth, y - dy * depth};
    spike.origin = origin;
    spike.width = width * scale;

    patch.spikes.push_back(spike);
  }

  return patch;
}

BasicGiraffeGenerator::Spike BasicGiraffeGenerator::generate_spike(
    Vector begin, Vector end) const
{
  return {};
}

Color mix_with(Color, Color, double first_amount);
BasicGiraffeGenerator::Patch BasicGiraffeGenerator::colored_patch(
    BasicGiraffeGenerator::Patch patch) const
{
  if (patch.points.size() == 0) return patch;

  std::uniform_real_distribution<double> dist(0, 2 * M_PI);
  std::default_random_engine re;
  auto angle = dist(re);

  Vector s = *std::next(patch.points.begin(), rand() % patch.points.size());
  Vector s2 = s * 2 - patch.center;
  for (auto point : patch.points)
  {
    Color color = {0, 0, 0};
    for (int dx = 0; dx < 2; dx++)
      for (int dy = 0; dy < 2; dy++)
      {
        int dx2 = dx;
        int dy2 = dy;
        if (dx == 0) dx2 = -1;
        if (dy == 0) dy2 = -1;

        Vector p = {point.x + dx2 / 2.0, point.y + dy2 / 2.0};
        Color c = {0, 0, 0};
        if (inside_patch(patch, p) / 4.0)
          c = patch_color_at(p, patch);
        else
          c = properties.colors.gap;

        color.r += c.r / 4;
        color.g += c.g / 4;
        color.b += c.b / 4;
      }

    patch.colors[point] = color;
  }

  return patch;
}

bool BasicGiraffeGenerator::inside_patch(
    const BasicGiraffeGenerator::Patch& patch, Vector p) const
{
  auto scale = sqrt(properties.scale);

  std::vector<std::pair<double, int>> dst_pairs(patch_points.size());
  std::vector<double> dst(patch_points.size());
  std::vector<int> dst_indices(patch_points.size());
  for (size_t i = 0; i < patch_points.size(); i++)
    dst_pairs[i] = {distance(p, patch_points[i]), i};
  sort(dst_pairs.begin(), dst_pairs.end());

  for (size_t i = 0; i < patch_points.size(); i++)
  {
    dst[i] = dst_pairs[i].first;
    dst_indices[i] = dst_pairs[i].second;
  }

  auto p1 = patch_points[dst_indices[0]];
  auto p2 = patch_points[dst_indices[1]];
  auto p3 = patch_points[dst_indices[2]];

  auto d1 = distance_from_bisector(p1, p2, p);
  auto d2 = distance_from_bisector(p1, p3, p);

  auto d = fmin(d1, d2);
  double gap = gap_between_patches(p1, p2);
  double gap2 = gap_between_patches(p1, p3);

  double g1 = gap * scale;
  double g2 = gap2 * scale;

  gap += edge_distortion_at(p, p1);
  gap2 += edge_distortion_at(p, p1);

  gap *= scale;
  gap2 *= scale;

  Color color;

  for (const Spike& spike : patch.spikes)
    if (inside_spike(patch, spike, p)) return false;

  if (d1 < gap || d2 < gap2)
    return false;
  else
    return true;
}

bool BasicGiraffeGenerator::inside_spike(
    const Patch& patch, const Spike& spike, Vector p) const
{
  double scale = sqrt(properties.scale);
  Vector v1 = Vector(patch.center) - p;
  Vector v2 = spike.origin - p;
  Vector v3 = spike.origin - patch.center;

  double d = fabs(cross(v1, v2)) / length(v3);
  if (length(v1) < length(v2 + v3)) d = length(v2);

  d += noise.accumulatedOctaveNoise1D(scale * length(v2) / 10.0, 3) *
       properties.patches.edge.roughness_strength * scale;

  d += noise.accumulatedOctaveNoise1D(scale * length(v2) / 10.0, 3) * scale *
       1.5;

  return d < spike.width;
}

Color BasicGiraffeGenerator::patch_color_at(
    Vector p, const BasicGiraffeGenerator::Patch& patch) const
{
  double n1 = noise.accumulatedOctaveNoise2D_0_1(p.x / 16, p.y / 16, 8);
  double n2 = noise.accumulatedOctaveNoise2D(p.x / 16, p.y / 16, 8);

  Point point(p.x, p.y);
  if (second_closest_index.contains(point) && patch_index.contains(point))
  {
    auto p1 = patch_points[patch_index.at(point)];
    auto p2 = patch_points[second_closest_index.at(point)];
    auto r = distance(p, p1) / distance(p, p2);
    n1 = n1 + 0.5 * logistic(0.6 - r);
  }

  double n3 = secondary_tint_at(p);

  Color c = properties.colors.patch;
  c = mix_with(properties.colors.middle_tint, c, n1);
  c = mix_with(properties.colors.secondary_tint, c, n3);

  return shade_at(p, c);
}

std::vector<Point> BasicGiraffeGenerator::generate_points(
    const PatternProperties& properties, const PointGenerator& generator)
{
  double a1 = area({512, 512});
  double a2 = area(properties.size);

  // Adjust number of points to preserve scale
  double point_scale =
      a2 / (properties.scale * properties.patches.size.scale * a1);
  size_t points = DEFAULT_PATCH_COUNT * point_scale;
  return generator.generate_points(points);
}

Color BasicGiraffeGenerator::color_at(Point p) const
{
  int i = patch_index.at(p);
  return patches[i].colors.at(p);
}

// For patches with centers in a and b, what should be gap between their borders
double BasicGiraffeGenerator::gap_between_patches(Point a, Point b) const
{
  double scale = sqrt(properties.scale);
  double n = noise.accumulatedOctaveNoise2D_0_1(
      scale * a.x / 16.0, scale * b.y / 16.0, 1);

  return n * (properties.patches.size.max_gap -
              properties.patches.size.min_gap) +
         properties.patches.size.min_gap;
}

double BasicGiraffeGenerator::secondary_tint_at(Vector p) const
{
  auto scale = sqrt(properties.scale);
  auto secondary_tint =
      noise.accumulatedOctaveNoise2D_0_1(scale * p.x / 16, scale * p.y / 16, 4);
  if (secondary_tint < 0.5) return 0;
  return secondary_tint * 0.5;
}

double BasicGiraffeGenerator::edge_distortion_at(Vector p, Point center) const
{
  double scale = sqrt(properties.scale);
  double angle = atan2(p.y - center.y, p.x - center.x);
  double freq = properties.patches.edge.roughness_frequency;

  auto roughness = noise.accumulatedOctaveNoise1D(
      angle * freq, properties.patches.edge.roughness_octaves);

  freq = properties.patches.edge.distortion_frequency;
  auto distortion = noise.accumulatedOctaveNoise1D_0_1(
      angle * freq, properties.patches.edge.distortion_octaves);

  distortion -= 0.5;

  distortion *= properties.patches.edge.distortion_strength * scale;
  roughness *= properties.patches.edge.roughness_strength * scale;

  return distortion + roughness;
}

Color mix_with(Color c1, Color c2, double first_amount)
{
  double d = first_amount;
  int r = c1.r * d + c2.r * (1 - d);
  int g = c1.g * d + c2.g * (1 - d);
  int b = c1.b * d + c2.b * (1 - d);
  return {r, g, b};
}

template <typename T>
T clamp(T value, T min, T max)
{
  if (value < min) return min;
  if (value > max) return max;
  return value;
}

// How bright should be patch at a given point
Color BasicGiraffeGenerator::shade_at(Vector p, Color c) const
{
  auto scale = sqrt(properties.scale);
  auto amount =
      noise.accumulatedOctaveNoise2D(scale * p.x / 16, scale * p.y / 16, 5);

  amount = 1 + 0.2 * amount;
  c.r *= amount;
  c.g *= amount;
  c.b *= amount;
  c.r = clamp(c.r, 0, 255);
  c.g = clamp(c.g, 0, 255);
  c.b = clamp(c.b, 0, 255);
  return c;
}
