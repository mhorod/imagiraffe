# Example: Color modification to make elemental giraffes

from generator import *

WIDTH = 256
HEIGHT = 256
SCALE = 0.25

water_colors = ColorParameters((42, 157, 244), (208, 239, 255), (24, 123, 205),
                               (47, 127, 173))

earth_colors = ColorParameters((163, 191, 69), (210, 225, 144), (97, 123, 48),
                               (116, 146, 58))

fire_colors = ColorParameters((254, 141, 0), (255, 255, 207), (226, 69, 0),
                              (254, 203, 121))

air_colors = ColorParameters((231, 241, 245), (255, 251, 251), (239, 247, 251),
                             (199, 214, 217))
run_params(
    Parameters("images/elemental/water_giraffe.png", WIDTH, HEIGHT, SCALE, 0,
               water_colors))
run_params(
    Parameters("images/elemental/earth_giraffe.png", WIDTH, HEIGHT, SCALE, 2,
               earth_colors))

run_params(
    Parameters("images/elemental/fire_giraffe.png", WIDTH, HEIGHT, SCALE, 4,
               fire_colors))
run_params(
    Parameters("images/elemental/air_giraffe.png", WIDTH, HEIGHT, SCALE, 7,
               air_colors))
