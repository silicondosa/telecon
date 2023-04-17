#pragma once

#include "chartdir.h"

/**
 * Describes what kind of line the the given plot uses to connect points.
 */
enum PlotLineType
{
    /**
     * A solid line.
     */
    LT_SOLID,
    /**
     * A dashed line.
     */
    LT_DASHED
};

/**
 * Describes what color a line or symbol will have.
 * In general, colors are represented as RGB colors, with one byte for each channel. These enumerators are just aliases for the colors they represent.
 * This enum also provides the special color COLOR_DEFAULT, documented below.
 */
enum PlotColor
{
    /**
     * This color has special behavior depending on the context in which it is used, according to the following rules (in order of priority):
     * -# If used for a plot's SymbolStyle, and that plot has a LineStyle, the symbol color will match the line color.
     * -# If used for a plot in a chart's add plot method, will use the color indicated by the chart's ::ColorSequenceMode.
     * -# Otherwise, defaults to black.
     */
    COLOR_DEFAULT = -1L,
    COLOR_BLACK = 0x000000,
    COLOR_GRAY = 0x777777,
    COLOR_RED = 0xff0000,
    COLOR_GREEN = 0x00ff00,
    COLOR_BLUE = 0x0000ff,

    // Names are chosen based on the closest matching HTML color code
    // Note however that the hex values are NOT identical to the HTML color

    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_CRIMSON = 0xa50026,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_SIENNA = 0xd73027,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_ORANGE = 0xf46d43,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_TAN = 0xfdae61,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_KHAKI = 0xfee090,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_ALICE_BLUE = 0xe0f3f8,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_LIGHT_BLUE = 0xabd9e9,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_CORNFLOWER_BLUE = 0x74add1,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_STEEL_BLUE = 0x4575b4,
    /** Used in ::ColorSequenceMode CSM_DIVERGING. */
    COLOR_DIVERGING_ROYAL_BLUE = 0x313695 // Actually also closest to steel blue; royal blue was next
};

/**
 * Describes the symbol that a plot will place to represent each data point.
 */
enum PlotSymbol
{
    /** Does not use a symbol; data points are left unmarked. */
    SYMBOL_NO_SYMBOL,
    /** Marks each data point with a circle. */
    SYMBOL_CIRCLE,
    /** Marks each data point with a square. */
    SYMBOL_SQUARE,
    /** Marks each data point with a triangle. */
    SYMBOL_TRIANGLE,
    /** Marks each data point with a diamond (a square rotated 45 degrees). */
    SYMBOL_DIAMOND,
    /** Marks each data point with a cross (a times sign, or a plus sign rotated 45 degrees). */
    SYMBOL_CROSS,
    /** Marks each data point with a plus sign. */
    SYMBOL_PLUS,
    /** Marks each data point with a five-pointed star. */
    SYMBOL_STAR
};