#include "PerlinNoise/PerlinNoise.hpp"
#include "basic_giraffe_generator.hpp"
#include "basic_point_generator.hpp"
#include "generator.hpp"
#include "giraffes.hpp"
#include "png/png.hpp"

const size_t WIDTH = 256;
const size_t HEIGHT = 256;

// Adds a slight blur to smooth out edges
Color adjusted_color(Point p, const GiraffeGenerator& generator)
{
  Color current = generator.color_at(p);
  if (current.r + current.b + current.g < 500) return current;
  Color c = {0, 0, 0};
  int samples = 0;
  for (int dx = -1; dx < 2; dx++)
    for (int dy = -1; dy < 2; dy++)
    {
      if (dx * dx == dy * dy) continue;
      samples++;
      auto c1 = generator.color_at({p.x + dx, p.y + dy});
      c.r += c1.r;
      c.g += c1.g;
      c.b += c1.b;
    }
  c.r /= samples;
  c.g /= samples;
  c.b /= samples;
  return c;
}

int main()
{
  srand(time(NULL));

  const siv::PerlinNoise perlin(rand());
  png::image<png::rgb_pixel> image(WIDTH, HEIGHT);

  PatternProperties properties = {
      {WIDTH, HEIGHT},
      0.25,
      AngolanGiraffe::default_colors,
      AngolanGiraffe::default_patches};

  auto point_generator = BasicPointGenerator(
      {properties.size.width, properties.size.height},
      properties.patches.min_to_max_size_ratio);

  auto generator = BasicGiraffeGenerator(properties, point_generator);

  auto shade_noise = siv::PerlinNoise(rand());

  double frequency = 8;
  double octaves = 4;
  double fx = WIDTH / frequency;
  double fy = HEIGHT / frequency;

  for (size_t x = 0; x < WIDTH; x++)
    for (size_t y = 0; y < HEIGHT; y++)
    {
      auto color =
          adjusted_color({static_cast<int>(x), static_cast<int>(y)}, generator);
      image[y][x] = png::rgb_pixel(color.r, color.g, color.b);
    }
  image.write("V.png");
}

