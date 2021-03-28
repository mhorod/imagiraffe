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
      50, 1,

      16, 5, 6,

      5,
  };
};

struct WestAfricanGiraffe
{
  static constexpr GiraffeColors default_colors = {
      {200, 160, 100},
      {241, 225, 203},
      {178, 132, 79},
      {124, 86, 51},
  };

  static constexpr GiraffePatches default_patches = {
      20, 0.7,

      16, 5,   6,

      5,
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

  static constexpr GiraffePatches default_patches = {
      15, 0.5,

      4,  8,   6,

      5,
  };
};

struct KordofanGiraffe
{
  static constexpr GiraffeColors default_colors = {
      {175, 140, 110},
      {255, 252, 215},
      {75, 58, 42},
      {97, 70, 43},
  };

  static constexpr GiraffePatches default_patches = {
      15, 0.5,

      3,  16,  10,

      2,
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
      30, 0.75,

      15, 16,   0.8,

      3,

      2,  -0.4, 30,
  };
};

#endif
