#pragma once

#include <array>
#include "enums.h"

static const std::array<int, 10> CSM_COLORS_DIVERGING {
    COLOR_DIVERGING_CRIMSON,
    COLOR_DIVERGING_SIENNA,
    COLOR_DIVERGING_ORANGE,
    COLOR_DIVERGING_TAN,
    COLOR_DIVERGING_KHAKI,
    COLOR_DIVERGING_ALICE_BLUE,
    COLOR_DIVERGING_LIGHT_BLUE,
    COLOR_DIVERGING_CORNFLOWER_BLUE,
    COLOR_DIVERGING_STEEL_BLUE,
    COLOR_DIVERGING_ROYAL_BLUE
};

/**
 * Describes what mode a chart will use for default colors.
 * A chart that constructs a default-color plot will assign the plot a color chosen by cycling through its associated colors.
 * Plots with manually chosen colors are unaffected by the color sequence mode.
 */
enum ColorSequenceMode
{
    /** All colors will be black.*/
    CSM_BLACK,
    /** A set of 10 colorblind-friendly diverging colors that go smoothly from red to blue.*/
    CSM_DIVERGING
};


