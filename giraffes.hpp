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
        {5, 5, 0.8, 2},
        {1, 5, 1, 4, 2.5, 5},
        {0, 0, 0},
    },
};

const GiraffeDefaults WestAfricanGiraffe{
    {
        {200, 160, 100},
        {230, 225, 203},
        {142, 99, 56},
        {124, 86, 51},
    },

    {
        {10, 10, 1, 2},
        {0.2, 6, 2, 4, 2.5, 4},
        {0, 0, 0},
    },
};

const GiraffeDefaults NubianGiraffe = {
    {
        {191, 150, 94},
        {255, 252, 215},
        {110, 74, 40},
        {154, 114, 74},
    },

    {
        {2, 20, 0.2, 10},
        {2, 8, 2, 5, 1, 5},
        {0, 0, 0},
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
        {8, 20, 0.2, 20},
        {0.75, 20, 6, 4, 2, 8},
        {0, 0, 0},
    },
};

const GiraffeDefaults AngolanGiraffe = {
    {
        {162, 127, 83},
        {209, 205, 170},
        {60, 31, 15},
        {112, 75, 38},
    },

    {
        {8, 20, 0.2, 20},
        {0.75, 20, 6, 4, 2, 8},
        {0, 0, 0},
    },
};

#endif
