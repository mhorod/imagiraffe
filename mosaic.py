from PIL import Image
import run

w = 64
h = 64

species = 9
samples = 5

result = Image.new('RGB', (samples * w, species * h))

for i in range(species):
    for j in range(samples):
        scale = 2**(j - 4) * (1 / 16)
        print(i, j)
        run.run_args('A.png', i, w, h, scale)
        with Image.open("A.png") as im:
            result.paste(im, (w * j, h * i))

result.save("M.png")
