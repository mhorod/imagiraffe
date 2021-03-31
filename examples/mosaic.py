# Example: Mosaic
# Generates an image composed of all species in different scales, with default settings

from PIL import Image
from generator import *
import os

# Size of single tile
w = 64
h = 64

species = 9
samples = 5

result = Image.new('RGB', (samples * w, species * h))

for i in range(species):
    for j in range(samples):
        scale = 2**(j - 4) * (1 / 16)
        run_params(Parameters('tmp.png', w, h, scale, i))
        with Image.open("tmp.png") as im:
            result.paste(im, (w * j, h * i))

os.remove('tmp.png')
result.save("mosaic.png")
