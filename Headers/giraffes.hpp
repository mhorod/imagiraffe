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
        {162, 127, 83},
        {240, 230, 180},
        {62, 44, 23},
        {112, 75, 38},
    },

    {
        {1, 4, 20, 0.2, 20},
        {0.75, 20, 6, 4, 2, 8},
        {0.5, 10, 20, 0, 1},
    },
};

const GiraffeDefaults SouthAfricanGiraffe = {
    {
        {162, 127, 70},
        {255, 237, 180},
        {76, 41, 28},
        {129, 75, 38},
    },

    {
        {1.5, 8, 20, 0.4, 20},
        {0.75, 40, 6, 4, 2, 8},
        {0.7, 50, 70, 2, 4},
    },
};

const GiraffeDefaults RothschildGiraffe = {
    {
        {184, 130, 92},
        {250, 222, 183},
        {74, 54, 44},
        {112, 75, 38},
    },

    {
        {1.75, 10, 20, 0.8, 20},
        {2, 10, 6, 4, 2, 8},
        {0.5, 5, 10, 0, 3},
    },
};

const GiraffeDefaults ThornicroftGiraffe = {
    {
        {157, 96, 39},
        {253, 226, 196},
        {60, 30, 25},
        {109, 51, 16},
    },

    {
        {1.5, 8, 20, 0.7, 20},
        {0.75, 20, 6, 4, 2, 8},
        {0.5, 60, 70, 1, 4},
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
        {0.8, 30, 50, 4, 7},
    },
};

#endif
