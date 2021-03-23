import random
import math
from PIL import Image
from PIL import ImageColor
from perlin_noise import PerlinNoise

WIDTH = 150
HEIGHT = 150

TRIES = 50
MIN_DISTANCE = 10
POINT_COUNT = 10


def rand_point():
    x = random.randint(0, WIDTH)
    y = random.randint(0, HEIGHT)
    return (x, y)


def distance(p1, p2):
    return ((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)**0.5


def generate_points(point_count, tries=20):
    points = []
    for i in range(point_count):
        for _ in range(tries):
            p = rand_point()
            ok = True
            for q in points:
                if distance(p, q) < MIN_DISTANCE + random.randint(-10, 10):
                    ok = False
                    break
            if ok:
                points.append(p)
                break
    return points


def between(c1, c2, r):
    return tuple([int(c1[i] * r + c2[i] * (1 - r)) for i in range(3)])


def sigmoid(x):
    return 1 / (1 + math.exp(-x))


class NoiseMap:
    def __init__(self):
        self.noise = PerlinNoise(octaves=5, seed=1)
        self.space_noise = PerlinNoise(octaves=20, seed=2)
        self.n1 = PerlinNoise(octaves=3)
        self.n2 = PerlinNoise(octaves=6)
        self.n3 = PerlinNoise(octaves=12)
        self.n4 = PerlinNoise(octaves=24)

    def get_noise(self, x, y):
        v = self.n1([x, y]) + 0.5 * self.n2([x, y]) + 0.25 * self.n3(
            [x, y]) + 0.125 * self.n4([x, y])

        return v / (1 + 0.5 + 0.25 + 0.125)


def color_at(x, y, points, noise_map):
    SPACE = (240, 230, 190)
    PATCH = (128, 69, 49)

    dists = sorted([distance((x, y), p) for p in points])
    d = dists[1] - dists[0]
    d2 = dists[2] - dists[1]

    x1, y1 = x / WIDTH, y / HEIGHT

    n = (1 + noise_map.noise([x1, y1])) / 2
    n2 = noise_map.space_noise([x1, y1])

    edge = noise_map.get_noise(x1, y1)

    space = False
    if d < 6 - 2 * n2 + 4 / (d2 + 1):
        color = SPACE
        m = n2 * 0.5 + 0.5 + n * 0.25
        color = tuple(int(i * (0.5 + m * 0.5)) for i in color)
        space = True
    else:
        color = PATCH
        n = n * 0.5 + 0.5
        n = (1 + edge) / 2
        color = tuple(int(i * n) for i in color)

    return color, space


def main():
    points = generate_points(20)
    noise_map = NoiseMap()
    image = Image.new("RGB", (WIDTH, HEIGHT))
    for x in range(WIDTH):
        for y in range(HEIGHT):
            color, space = color_at(x, y, points, noise_map)
            s = [0, 0, 0]
            if space:
                for dx in range(-1, 2):
                    for dy in range(-1, 2):
                        ca, _ = color_at(x + dx, y + dy, points, noise_map)
                        for i in range(3):
                            s[i] += ca[i]
                color = [i // 9 for i in s]

            image.putpixel((x, y), tuple(color))

    image.save("V.png")


main()
