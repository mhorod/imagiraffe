#include "basic_giraffe_generator.hpp"

#include <iostream>

double logistic(double x) { return 1 / (1 + pow((0.75 - x) / x, 2)); }

const int DEFAULT_PATCH_COUNT = 40;

std::vector<Point> BasicGiraffeGenerator::generate_points(
    const PatternProperties& properties, const PointGenerator& generator)
{
  double a1 = area({512, 512});
  double a2 = area(properties.size);
  double point_scale = a2 / (properties.scale * a1);
  size_t points = DEFAULT_PATCH_COUNT * point_scale;
  return generator.generate_points(points);
}

Color mix_with(Color, Color, double first_amount);

// Calculates the distance of p from bisector of ab
double distance_from_bisector(Point a, Point b, Point p)
{
  auto d1 = distance(a, p);
  auto d2 = distance(b, p);
  auto d = distance(a, b);

  double v = d1 * d1 - d2 * d2;
  return fabs(v / (2 * d));
}

Color BasicGiraffeGenerator::color_at(Point p) const
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
  double gap = gap_between_points(p1, p2);
  double gap2 = gap_between_points(p1, p3);

  double g1 = gap * scale;
  double g2 = gap2 * scale;

  gap += edge_distortion_at(p, p1);
  gap2 += edge_distortion_at(p, p1);

  gap *= scale;
  gap2 *= scale;

  int c = 128 + 5 * edge_distortion_at(p, p1);

  double mix1 = (gap - d1 + 1) / 2;
  double mix2 = (gap2 - d2 + 1) / 2;
  bool m1 = mix1 > 0 && mix1 < 1 && d2 >= gap2;
  bool m2 = mix2 > 0 && mix2 < 1 && d1 >= gap;
  bool on_edge = m1 | m2;
  double mix = 0;
  if (m1) mix = mix1;
  if (m2) mix = mix2;

  Color color;

  if (d1 < gap || d2 < gap2)
  {
    color = properties.colors.gap;
    if (on_edge) color = mix_with(color, properties.colors.patch, mix);
  }
  else
  {
    double r = (dst[0] / (dst[0] + dst[1]));
    r = logistic(r);
    color = properties.colors.patch;
    color = mix_with(color, properties.colors.middle_tint, r);
    color =
        mix_with(color, properties.colors.secondary_tint, secondary_tint_at(p));
    if (on_edge) color = mix_with(color, properties.colors.gap, 1 - mix);
    color = shade_at(p, color);
  }
  return color;
}

double BasicGiraffeGenerator::gap_between_points(Point a, Point b) const
{
  double noise = patch_roughness_noise.accumulatedOctaveNoise2D_0_1(
      a.x / 16.0, b.y / 16.0, 10);

  noise = sin((double)a.x * b.y / a.y * b.x) * 0.5 + 0.5;
  return 0.5 * noise *
             (properties.patches.size.max_gap -
              properties.patches.size.min_gap) +
         properties.patches.size.min_gap;
}

double BasicGiraffeGenerator::patch_distortion_at(Point p) const { return 0; }

double BasicGiraffeGenerator::secondary_tint_at(Point p) const
{
  auto secondary_tint = secondary_tint_noise.accumulatedOctaveNoise2D_0_1(
      p.x / 32.0, p.y / 32.0, 16);
  return secondary_tint;
}

double BasicGiraffeGenerator::patch_roughness_at(Point p) const { return 0; }

double BasicGiraffeGenerator::edge_distortion_at(Point p, Point center) const
{
  double angle = atan2(p.y - center.y, p.x - center.x);
  double freq = properties.patches.edge.roughness_frequency;
  angle += center.x * center.y;

  auto roughness = patch_roughness_noise.accumulatedOctaveNoise1D(
      angle * freq, properties.patches.edge.roughness_octaves);

  freq = properties.patches.edge.distortion_frequency;
  angle += center.x * center.y;
  auto distortion = patch_roughness_noise.accumulatedOctaveNoise1D_0_1(
      angle * freq, properties.patches.edge.distortion_octaves);

  distortion -= 0.5;

  distortion *= properties.patches.edge.distortion_strength;
  roughness *= properties.patches.edge.roughness_strength;

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

Color BasicGiraffeGenerator::shade_at(Point p, Color c) const
{
  auto scale = properties.scale;
  auto amount = shade_noise.accumulatedOctaveNoise2D_0_1(
      scale * p.x / 32, scale * p.y / 32, 8);

  amount = 1 + (amount - 0.5) * 0.25;
  c.r *= amount;
  c.g *= amount;
  c.b *= amount;
  c.r = clamp(c.r, 0, 255);
  c.g = clamp(c.g, 0, 255);
  c.b = clamp(c.b, 0, 255);
  return c;
}
