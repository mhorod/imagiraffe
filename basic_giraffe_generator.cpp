#include "basic_giraffe_generator.hpp"

#include <iostream>

double logistic(double x) { return 1 / (1 + pow((0.75 - x) / x, 3)); }

const int DEFAULT_PATCH_COUNT = 30;

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

Color BasicGiraffeGenerator::color_at(Point p) const
{
  auto scale = properties.scale;
  double fx = scale * properties.size.width /
              properties.patches.patch_distortion_frequency;
  double fy = scale * properties.size.height /
              properties.patches.patch_distortion_frequency;

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

  double v = pow(dst[1], 2) - pow(dst[0], 2);
  double d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
  double b = (d + v / d) / 2;
  double gap = 2 * b - d;

  auto patch_distortion = patch_distortion_at(p);
  if (patch_distortion < 0) patch_distortion = 0;
  auto patch_roughness = patch_roughness_at(p);

  auto edge_distortion = edge_distortion_at(p, patch_points[dst_indices[0]]);

  double d1 = dst[1] - dst[0];
  double d2 = dst[2] - dst[1];

  double gap_size =
      properties.patches.gap_size + edge_distortion - patch_distortion;
  double gap_smooth = properties.patches.rounded_corners_strength / (d2 + 1);

  auto r = dst[0] / (dst[0] + dst[1]);
  auto r2 = r + patch_roughness;

  Color color;
  if (gap * patch_roughness + gap_smooth < scale * gap_size)
  {
    color = properties.colors.gap;
  }
  else
  {
    r = logistic(r);
    color = mix_with(
        properties.colors.patch, properties.colors.secondary_tint,
        secondary_tint_at(p));
    color = mix_with(color, properties.colors.middle_tint, r);
  }

  return shade_at(p, color);
}

double BasicGiraffeGenerator::patch_distortion_at(Point p) const
{
  auto scale = properties.scale;
  double fx = scale * properties.size.width /
              properties.patches.patch_distortion_frequency;
  double fy = scale * properties.size.height /
              properties.patches.patch_distortion_frequency;
  auto patch_distortion = patch_distortion_noise.accumulatedOctaveNoise2D_0_1(
      p.x / fx, p.y / fy, 3);

  patch_distortion = (patch_distortion - 0.5) * 2;
  patch_distortion *= properties.patches.patch_distortion_strength;
  return patch_distortion;
}

double BasicGiraffeGenerator::secondary_tint_at(Point p) const
{
  auto secondary_tint =
      secondary_tint_noise.accumulatedOctaveNoise2D_0_1(p.x, p.y, 8);
  return secondary_tint;
}

double BasicGiraffeGenerator::patch_roughness_at(Point p) const
{
  auto scale = properties.scale;
  auto patch_roughness = patch_roughness_noise.accumulatedOctaveNoise2D_0_1(
      scale * p.x / 16, scale * p.y / 16, 8);

  patch_roughness = 0.5 * patch_roughness + 0.5;
  patch_roughness *= properties.patches.patch_roughness;
  // patch_roughness = logistic(patch_roughness);
  return patch_roughness;
}

double BasicGiraffeGenerator::edge_distortion_at(Point p, Point center) const
{
  double angle = atan2(p.y - center.y, p.x - center.x);
  double freq = properties.patches.spike_frequency;
  angle += center.x * center.y;
  auto patch_roughness =
      patch_roughness_noise.noise1D(angle * properties.patches.spike_frequency);

  if (patch_roughness < properties.patches.spike_threshold)
    patch_roughness *= properties.patches.spike_strength;
  // patch_roughness = logistic(patch_roughness);
  return patch_roughness;
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
