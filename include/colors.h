#pragma once

#include <array>

using namespace std;

static const array<int, 10> CSM_COLORS_DIVERGING {
    0xa50026,
    0xd73027,
    0xf46d43,
    0xfdae61,
    0xfee090,
    0xe0f3f8,
    0xabd9e9,
    0x74add1,
    0x4575b4,
    0x313695
};

enum ColorSequenceMode
{
    CSM_BLACK,
    CSM_DIVERGING
};


