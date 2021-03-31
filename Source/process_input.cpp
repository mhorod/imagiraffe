#include "process_input.hpp"

#include <iostream>

void read_color(Color& c) { std::cin >> c.r >> c.g >> c.b; }
Parameters read_parameters()
{
  Parameters p;
  std::cin >> p.filename;
  std::cin >> p.width >> p.height;
  std::cin >> p.scale;
  std::cin >> p.giraffe;

  bool colors_set;
  std::cin >> colors_set;
  if (colors_set)
  {
    GiraffeColors c;
    read_color(c.patch);
    read_color(c.gap);
    read_color(c.middle_tint);
    read_color(c.secondary_tint);
    p.colors = c;
  }

  bool patches_set;
  std::cin >> patches_set;
  if (patches_set)
  {
    GiraffePatches g;
    std::cin >> g.size.scale;
    std::cin >> g.size.min_gap;
    std::cin >> g.size.max_gap;
    std::cin >> g.size.min_to_max_ratio;
    std::cin >> g.size.standard_deviation;

    std::cin >> g.edge.distortion_frequency;
    std::cin >> g.edge.distortion_strength;
    std::cin >> g.edge.distortion_octaves;
    std::cin >> g.edge.roughness_frequency;
    std::cin >> g.edge.roughness_strength;
    std::cin >> g.edge.roughness_octaves;

    std::cin >> g.spikes.min_count;
    std::cin >> g.spikes.max_count;
    std::cin >> g.spikes.min_depth;
    std::cin >> g.spikes.max_depth;
    std::cin >> g.spikes.min_width;
    std::cin >> g.spikes.max_width;
    p.patches = g;
  }

  return p;
}
