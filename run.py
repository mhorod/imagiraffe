from subprocess import Popen, PIPE
import sys

MAX_IMAGE_SIZE = 1024


def run(config_text):
    print("Your giraffe is generating, please wait")
    p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    out = p.communicate(input=bytes(config_text, "ascii"))[1]
    if out:
        print("An error occured")
        print(out.decode("ascii"))
    else:
        print("Your giraffe is ready")


def run_args(filename, giraffe, width, height, scale):
    config_text = f'''
    {filename}
    {giraffe}
    {width}
    {height}
    {scale}
    '''
    run(config_text)


def generate_sample_images():
    for i in range(0, 9):
        for j in range(0, 10):
            scale = 1 / 16 * 2**(j % 5)
            run_args(f'images/{i}-{j}.png', i, 128, 128, scale)
            # print(f'![s{i}-{j}](images/{i}-{j}.png)')


def ask_yes_no(question, default):
    y = "Y" if default == True else "y"
    n = "N" if default == False else "n"
    question += f" [{y}/{n}] "

    answer = input(question)
    if answer == None: return default
    answer = answer.lower()
    if answer == "y" or answer == "yes": return True
    if answer == "n" or answer == "no": return False


def ask_until_valid(question, validate):
    while True:
        answer = input(question)
        error = validate(answer)
        if len(error) == 0: return answer
        print(error)


def enter_number(x, minimum, maximum):
    error = f"Please enter a number between {minimum} and {maximum}"
    if x.isdecimal():
        x = int(x)
        if x < minimum or x > maximum:
            return error
        return ""
    else:
        return error


def enter_float(x):
    try:
        float(x)
    except:
        return "Please enter a real number"
    return ""


def load_configuration_from_user_input():
    print("Welcome to giraffe generator 2021\n")

    giraffes = [
        "ReticulatedGiraffe", "WestAfricanGiraffe", "NubianGiraffe",
        "KordofanGiraffe", "AngolanGiraffe", "SouthAfricanGiraffe",
        "RothschildGiraffe", "ThornicroftGiraffe", "MasaiGiraffe"
    ]

    print("Available giraffes: ")
    for index, name in enumerate(giraffes):
        print(f"{index}: {name}")

    print()
    choice_validation = lambda x: enter_number(x, 0, len(giraffes) - 1)
    choice = int(ask_until_valid("Your choice: ", choice_validation))

    size_validation = lambda x: enter_number(x, 0, MAX_IMAGE_SIZE)
    width = int(ask_until_valid("Image width: ", size_validation))
    height = int(ask_until_valid("Image height: ", size_validation))

    scale = float(ask_until_valid("Image scale: ", enter_float))

    colors = None
    patches = None
    if ask_yes_no("Do you want to specify colors?", False):
        colors = load_colors_from_user_input()
    if ask_yes_no("Do you want to specify patches?", False):
        patches = load_patches_from_user_input()

    filename = ask_until_valid("Enter result file name: ", lambda x: "")

    return [filename, choice, width, height, scale, colors, patches]


def is_valid_color(color):
    if len(color) == 0: return False
    if color[0] == "#":
        return is_valid_hex(color)
    else:
        return is_valid_rgb(color)


def is_valid_hex(color):
    color = color[1:]
    if len(color) != 6: return False
    for i in range(0, 6, 2):
        try:
            c = int(color[i:i + 2], 16)
            if c > 255: return False
        except:
            return False

    return True


def is_valid_rgb(color):
    if len(color) < 2: return False
    color = color[1:-1]
    if len(values) != 3: return False
    for v in values:
        v = v.strip()
        if not v.isdecimal() or int(v) < 0 or int(v) > 255: return False
    return True


def parse_hex(color):
    color = color[1:]
    return [int(color[i:i + 2], 16) for i in range(0, 6, 2)]


def parse_color(color):
    if color[0] == "#": return parse_hex(color)
    else: return parse_rgb(color)


def parse_rgb(color):
    color = color[1:-1]
    values = color.split(',')
    return [int(v) for v in values]


def enter_color(color):
    if not is_valid_color(color): return "Please enter a valid color"
    return ""


def load_colors_from_user_input():
    print("Color specification")
    print("Colors should be in #rrggbb or (r, g, b) format")
    print()
    patch_color = parse_color(ask_until_valid("Patch color: ", enter_color))
    gap_color = parse_color(ask_until_valid("Gap color: ", enter_color))
    middle_color = parse_color(ask_until_valid("Middle color: ", enter_color))
    secondary_color = parse_color(
        ask_until_valid("Secondary color: ", enter_color))

    return patch_color, gap_color, middle_color, secondary_color


def load_patches_from_user_input():
    print("Patch specification.")
    print("All values should be set as for a 512x512 image")
    print()
    print("Size")
    scale = float(ask_until_valid("Patch scale: ", enter_float))
    min_gap = float(
        ask_until_valid("Minimum gap between patches: ", enter_float))
    max_gap = float(
        ask_until_valid("Maximum gap between patches: ", enter_float))
    min_to_max_ratio = float(
        ask_until_valid("Min to max area ratio: ", enter_float))
    standard_deviation = float(
        ask_until_valid("Standard deviation of patch size", enter_float))

    print()
    print("Edges noise")
    distortion_frequency = float(
        ask_until_valid("Distortion frequency: ", enter_float))
    distortion_strength = float(
        ask_until_valid("Distortion strength: ", enter_float))
    distortion_octaves = float(
        ask_until_valid("Distortion octaves: ", enter_float))
    roughness_frequency = float(
        ask_until_valid("Roughness frequency: ", enter_float))
    roughness_strength = float(
        ask_until_valid("Roughness strength: ", enter_float))
    roughness_octaves = float(
        ask_until_valid("Roughness octaves: ", enter_float))

    return [
        scale, min_gap, max_gap, min_to_max_ratio, standard_deviation,
        distortion_frequency, distortion_strength, distortion_octaves,
        roughness_frequency, roughness_strength, roughness_octaves
    ]


def generate_config_text(config):
    config_text = ""
    for c in config[:-2]:
        config_text += str(c) + '\n'

    if config[-2] is not None:
        config_text += "1\n"
        config_text += "\n".join(
            str(" ".join(str(v) for v in c)) for c in config[-2]) + "\n"
    else:
        config_text += "0\n"

    if config[-1] is not None:
        config_text += "1\n"
        config_text += "patches"
        config_text += "\n".join(str(c) for c in config[-1])
    else:
        config_text += "0\n"

    return config_text


if __name__ == '__main__':
    if len(sys.argv) == 1:
        config = load_configuration_from_user_input()
        config_text = generate_config_text(config)
        print(config_text)
        run(config_text)
    #generate_sample_images()
