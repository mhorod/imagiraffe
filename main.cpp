#include "PerlinNoise/PerlinNoise.hpp"
#include "basic_giraffe_generator.hpp"
#include "basic_point_generator.hpp"
#include "generator.hpp"
#include "giraffes.hpp"
#include "png/png.hpp"

struct Parameters
{
  std::string filename;
  size_t giraffe;
  size_t width, height;
  double scale;
};

Parameters read_parameters()
{
  Parameters p;
  std::cin >> p.filename;
  std::cin >> p.giraffe;
  std::cin >> p.width >> p.height;
  std::cin >> p.scale;
  return p;
}

int main(int argc, char* argv[])
{
  auto parameters = read_parameters();

  srand(time(NULL));

  const siv::PerlinNoise perlin(rand());
  png::image<png::rgb_pixel> image(parameters.width, parameters.height);

  std::vector<GiraffeDefaults> giraffes = {
      ReticulatedGiraffe, WestAfricanGiraffe, NubianGiraffe, KordofanGiraffe,
      AngolanGiraffe};

  PatternProperties properties = {
      {parameters.width, parameters.height},
      parameters.scale,
      giraffes[parameters.giraffe].default_colors,
      giraffes[parameters.giraffe].default_patches};

  auto point_generator = BasicPointGenerator(
      {properties.size.width, properties.size.height}, properties.patches.size);

  auto generator = BasicGiraffeGenerator(properties, point_generator);

  auto shade_noise = siv::PerlinNoise(rand());

  double frequency = 8;
  double octaves = 4;
  double fx = parameters.width / frequency;
  double fy = parameters.height / frequency;

  for (size_t x = 0; x < parameters.width; x++)
    for (size_t y = 0; y < parameters.height; y++)
    {
      auto color =
          generator.color_at({static_cast<int>(x), static_cast<int>(y)});
      image[y][x] = png::rgb_pixel(color.r, color.g, color.b);
    }
  image.write(parameters.filename);
}

