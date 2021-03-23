#ifndef GIRAFFES_HPP
#define GIRAFFES_HPP

#include "generator.hpp"

struct ReticulatedGiraffe
{
  static constexpr GiraffeColors default_colors = {
      {128, 69, 49},
      {230, 210, 190},
      {128, 69, 49},
      {128, 69, 69},
  };

  static constexpr GiraffePatches default_patches = {
      10, 1,

      16, 5, 6,

      5,
  };
};

struct WestAfricanGiraffe
{
  static constexpr GiraffeColors default_colors = {
      {188, 147, 86},
      {241, 225, 177},
      {89, 54, 39},
      {80, 40, 20},
  };
};

struct NubianGiraffe
{
  static constexpr GiraffeColors default_colors = {
      {191, 150, 94},
      {255, 252, 215},
      {130, 84, 50},
      {154, 114, 74},
  };
};

struct KordofanGiraffe
{
  static constexpr GiraffeColors default_colors = {
      {162, 133, 93},
      {255, 252, 215},
      {77, 58, 44},
      {97, 70, 43},
  };
};

struct AngolanGiraffe
{
  static constexpr GiraffeColors default_colors = {
      {162, 127, 83},
      {219, 200, 170},
      {79, 44, 15},
      {112, 75, 38},
  };

  static constexpr GiraffePatches default_patches = {
      20, 0.75,

      15, 16,   5,

      3,
  };
};

#endif
