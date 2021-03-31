#ifndef PROCESS_INPUT_HPP
#define PROCESS_INPUT_HPP

#include <optional>
#include <string>

#include "generator.hpp"

// Paramaterization of the generator
struct Parameters
{
  std::string filename;
  size_t giraffe;
  size_t width, height;
  double scale;
  std::optional<GiraffeColors> colors;
  std::optional<GiraffePatches> patches;
};

// Read parameters from stdin
Parameters read_parameters();

#endif
