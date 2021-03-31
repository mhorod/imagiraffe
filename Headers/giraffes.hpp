#ifndef GIRAFFES_HPP
#define GIRAFFES_HPP

#include "generator.hpp"

struct GiraffeDefaults
{
  GiraffeColors default_colors;
  GiraffePatches default_patches;
};

const GiraffeDefaults ReticulatedGiraffe = {
    {
        {128, 69, 49},
        {215, 210, 190},
        {105, 50, 30},
        {130, 70, 50},
    },
    {
        {1, 5, 5, 0.8, 5},
        {1, 5, 1, 4, 2.5, 5},
    },
};

const GiraffeDefaults WestAfricanGiraffe{
    {
        {200, 160, 100},
        {230, 225, 203},
        {173, 135, 80},
        {180, 150, 80},
    },

    {
        {1, 10, 10, 1, 2},
        {0.2, 6, 2, 4, 2.5, 4},
    },
};

const GiraffeDefaults NubianGiraffe = {
    {
        {191, 150, 94},
        {255, 252, 215},
        {110, 74, 40},
        {184, 144, 82},
    },

    {
        {1, 2, 20, 0.2, 10},
        {2, 8, 2, 5, 1, 5},
    },
};

const GiraffeDefaults KordofanGiraffe = {
    {
        {190, 140, 85},
        {255, 252, 215},
        {82, 60, 40},
        {142, 113, 75},
    },

    {
        {1, 8, 20, 0.2, 20},
        {0.75, 20, 6, 4, 2, 8},
        {0, 0, 0},
    },
};

const GiraffeDefaults AngolanGiraffe = {
    {
        {163, 101, 39},
        {240, 230, 180},
        {88, 52, 23},
        {140, 103, 61},
    },

    {
        {1, 4, 20, 0.2, 20},
        {0.75, 20, 6, 4, 2, 8},
        {0, 1, 20, 30, 1, 2},
    },
};

const GiraffeDefaults SouthAfricanGiraffe = {
    {
        {162, 127, 70},
        {255, 237, 180},
        {122, 78, 31},
        {180, 133, 91},
    },

    {
        {1.5, 8, 20, 0.4, 20},
        {0.75, 40, 6, 4, 2, 8},
        {1, 4, 40, 60, 2, 8},
    },
};

const GiraffeDefaults RothschildGiraffe = {
    {
        {184, 130, 92},
        {250, 222, 183},
        {100, 83, 65},
        {165, 111, 80},
    },

    {
        {1.75, 10, 20, 0.8, 20},
        {2, 10, 6, 4, 2, 8},
        {2, 5, 8, 16, 0.5, 2},
    },
};

const GiraffeDefaults ThornicroftGiraffe = {
    {
        {128, 82, 59},
        {253, 226, 196},
        {100, 73, 64},
        {115, 87, 74},
    },

    {
        {1.5, 8, 20, 0.7, 20},
        {0.75, 20, 6, 4, 2, 8},
        {1, 5, 50, 60, 2, 3},
    },
};

const GiraffeDefaults MasaiGiraffe = {
    {
        {60, 51, 50},
        {255, 228, 199},
        {60, 50, 48},
        {108, 92, 92},
    },

    {
        {2, 8, 20, 0.9, 20},
        {0.75, 20, 6, 4, 2, 8},
        {4, 7, 30, 50, 2, 5},
    },
};

#endif
