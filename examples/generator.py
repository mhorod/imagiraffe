# Python interface for the generator

from subprocess import Popen, PIPE


class Parameters:
    def __init__(self,
                 filename,
                 width,
                 height,
                 scale,
                 giraffe,
                 colors=None,
                 patches=None):
        self.filename = filename
        self.width = width
        self.height = height
        self.scale = scale
        self.giraffe = giraffe
        self.colors = colors
        self.patches = patches

    def to_config_text(self):
        color_text = ("0" if self.colors is None else "1\n" +
                      self.colors.to_config_text())
        patch_text = ("0" if self.patches is None else "1\n" +
                      self.patches.to_config_text())
        return f'''
        {self.filename}
        {self.width}
        {self.height}
        {self.scale}
        {self.giraffe}
        {color_text}
        {patch_text}
        '''


class ColorParameters:
    def __init__(self, patch, gap, middle, secondary):
        self.patch = patch
        self.gap = gap
        self.middle = middle
        self.secondary = secondary

    def to_config_text(self):
        return f'''
        {self.color_to_string(self.patch)} 
        {self.color_to_string(self.gap)} 
        {self.color_to_string(self.middle)} 
        {self.color_to_string(self.secondary)} 
        '''

    def color_to_string(self, color):
        return " ".join(str(v) for v in color)


class PatchParameters:
    def __init__(self, size, edge, spikes):
        self.size = size
        self.edge = edge
        self.spikes = spikes

    def to_config_text(self):
        return f'''
        {self.size.to_config_text()}
        {self.edge.to_config_text()}
        {self.spikes.to_config_text()}
        '''


class PatchSize:
    def __init__(self, scale, min_gap, max_gap, min_to_max_ratio,
                 standard_deviation):
        self.scale = scale
        self.min_gap = min_gap
        self.max_gap = max_gap
        self.min_to_max_ratio = min_to_max_ratio
        self.standard_deviation = standard_deviation

    def to_config_text(self):
        return f'''
        {self.scale}
        {self.min_gap}
        {self.max_gap}
        {self.min_to_max_ratio}
        {self.standard_deviation}
        '''


class PatchEdge:
    def __init__(self, distortion, roughness):
        self.distortion = distortion
        self.roughness = roughness

    def to_config_text(self):
        return f'''
        {self.distortion.to_config_text()}
        {self.roughness.to_config_text()}
        '''


class NoiseParameters:
    def __init__(self, frequency, strength, octaves):
        self.frequency = frequency
        self.strength = strength
        self.octaves = octaves

    def to_config_text(self):
        return f'''
        {self.frequency}
        {self.strength}
        {self.octaves}
        '''


class PatchSpikes:
    def __init__(self, min_count, max_count, min_depth, max_depth, min_width,
                 max_width):
        self.min_count = min_count
        self.max_count = max_count
        self.min_depth = min_depth
        self.max_depth = max_depth
        self.min_width = min_width
        self.max_width = max_width

    def to_config_text(self):
        return f'''
        {self.min_count}
        {self.max_count}
        {self.min_depth}
        {self.max_depth}
        {self.min_width}
        {self.max_width}
        '''


def run(config_text):
    p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    out = p.communicate(input=bytes(config_text, "ascii"))[1]
    return out


def run_params(params):
    run(params.to_config_text())
