#pragma once

enum COLORS
{
    COLOR_DEFAULT = -1L,
    COLOR_BLACK = 0x000000,
    COLOR_GRAY = 0x777777,
    COLOR_RED = 0xff0000,
    COLOR_GREEN = 0x00ff00,
    COLOR_BLUE = 0x0000ff,
    // Names are chosen based on the closest matching HTML color code
    // Note that the hex values are NOT identical to the HTML color
    COLOR_DIVERGING_CRIMSON = 0xa50026,
    COLOR_DIVERGING_SIENNA = 0xd73027,
    COLOR_DIVERGING_ORANGE = 0xf46d43,
    COLOR_DIVERGING_TAN = 0xfdae61,
    COLOR_DIVERGING_KHAKI = 0xfee090,
    COLOR_DIVERGING_ALICE_BLUE = 0xe0f3f8,
    COLOR_DIVERGING_LIGHT_BLUE = 0xabd9e9,
    COLOR_DIVERGING_CORNFLOWER_BLUE = 0x74add1,
    COLOR_DIVERGING_STEEL_BLUE = 0x4575b4,
    COLOR_DIVERGING_ROYAL_BLUE = 0x313695 // Actually closest to steel blue; royal blue was next
};
