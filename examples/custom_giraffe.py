# Example: Customization of all settings
# It may not be the best giraffe tho

from generator import *

colors = ColorParameters((200, 200, 200), (240, 240, 240), (107, 65, 40),
                         (150, 150, 150))

size = PatchSize(1, 2, 30, 0.1, 10)
edge = PatchEdge(NoiseParameters(5, 20, 2), NoiseParameters(2, 5, 8))
spikes = PatchSpikes(50, 100, 10, 20, 2, 5)

patches = PatchParameters(size, edge, spikes)
params = Parameters("custom_giraffe1.png",
                    256,
                    256,
                    1 / 8,
                    0,
                    colors=colors,
                    patches=patches)
run_params(params)

params.colors.gap = (30, 30, 30)
params.colors.patch = (124, 49, 30)
edge.distortion.strength *= 3
spikes.max_count = 20
spikes.min_count = 10
size.scale = 2
params.filename = "custom_giraffe2.png"
run_params(params)
