from subprocess import Popen, PIPE
import sys


def run(filename, giraffe, width, height, scale):
    config_input = f'''
    {filename}
    {giraffe}
    {width} {height}
    {scale}
    '''

    p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    out = p.communicate(input=bytes(config_input, "ascii"))[1]


def generate_sample_images():
    for i in range(0, 5):
        for j in range(0, 10):
            scale = 1 / 16 * 2**(j % 5)
            run(f'images/{i}-{j}.png', i, 128, 128, scale)
            # print(f'![s{i}-{j}](images/{i}-{j}.png)')


if __name__ == '__main__':
    run('A.png', sys.argv[1], 128, 128, 1 / 16)
    generate_sample_images()
