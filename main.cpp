#include "PerlinNoise/PerlinNoise.hpp"
#include "basic_giraffe_generator.hpp"
#include "basic_point_generator.hpp"
#include "generator.hpp"
#include "giraffes.hpp"
#include "png/png.hpp"
#include "process_input.hpp"

int main(int argc, char* argv[])
{
  srand(time(NULL));
  auto parameters = read_parameters();

  std::vector<GiraffeDefaults> giraffes = {
      ReticulatedGiraffe, WestAfricanGiraffe, NubianGiraffe,
      KordofanGiraffe,    AngolanGiraffe,     SouthAfricanGiraffe,
      RothschildGiraffe,  ThornicroftGiraffe, MasaiGiraffe};

  if (!parameters.colors.has_value())
    parameters.colors = giraffes[parameters.giraffe].default_colors;
  if (!parameters.patches.has_value())
    parameters.patches = giraffes[parameters.giraffe].default_patches;

  PatternProperties properties = {
      {parameters.width, parameters.height},
      parameters.scale,
      parameters.colors.value(),
      parameters.patches.value()};

  auto point_generator = BasicPointGenerator(
      {properties.size.width, properties.size.height}, properties.patches.size);
  auto generator = BasicGiraffeGenerator(properties, point_generator);

  png::image<png::rgb_pixel> image(parameters.width, parameters.height);
  for (size_t x = 0; x < parameters.width; x++)
    for (size_t y = 0; y < parameters.height; y++)
    {
      auto color =
          generator.color_at({static_cast<int>(x), static_cast<int>(y)});
      image[y][x] = png::rgb_pixel(color.r, color.g, color.b);
    }
  image.write(parameters.filename);
}

