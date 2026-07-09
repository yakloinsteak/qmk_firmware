#pragma once

enum layer_number {
    BASE = 0,
    TAB_HOLD_LAYER,
    LTHUMB_2R,
    RTHUMB_2L,
    THUMBS_INWARD, // both the previous together
    MACROS,
    UTIL,
    SYMBOLS,
    WARP,
};

#define LOWER  LTHUMB_2R
#define UPPER  RTHUMB_2L
#define ADJUST THUMBS_INWARD
