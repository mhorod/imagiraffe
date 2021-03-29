import os
from PIL import Image
import matplotlib.pyplot as plt

TOLERANCE = 200
THRESHOLD = 500


def area_data(name):
    with Image.open(name) as img:
        px = img.load()
        w, h = img.size
    data = {}

    for x in range(w):
        for y in range(h):
            color = px[x, y]
            if color in data:
                data[color] += 1
            else:
                data[color] = 1

    s = [d for d in sorted(data.values()) if d > THRESHOLD]
    return min(s), s[len(s) // 2], max(s), s


def graph_data(data):
    m1 = min(data)
    m2 = max(data)
    x = []
    y = []
    for mid in range(TOLERANCE, m2, TOLERANCE):
        x.append(mid)
        y.append(len([p for p in data if abs(p - mid) <= TOLERANCE]))

    plt.plot(x, y)


data = []
alldata = []
for _ in range(20):
    os.system('./main A.png')
    d = area_data('A.png')
    data.append(d[:3])
    alldata += d[3]

for i in range(len(data[0])):
    graph_data([d[i] for d in data])
graph_data(alldata)

plt.show()
