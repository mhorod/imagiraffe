# Example: Generating many separate images with different scales

from generator import *

SPECIES = 9
IMAGES = 10

WIDTH = 128
HEIGHT = 128

for i in range(0, SPECIES):
    for j in range(0, IMAGES):
        scale = 1 / 16 * 2**(j % 5)
        run_params(Parameters(f'images/{i}-{j}.png', WIDTH, HEIGHT, scale, i))
