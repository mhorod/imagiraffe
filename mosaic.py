from PIL import Image
import run

w = 128
h = 128
t = 5

result = Image.new('RGB', (t * w, t * h))

for i in range(t):
    for j in range(t):
        scale = 2**(j - 4)
        run.run('A.png', i, w, h, scale)
        with Image.open("A.png") as im:
            result.paste(im, (w * j, h * i))

result.save("M.png")
