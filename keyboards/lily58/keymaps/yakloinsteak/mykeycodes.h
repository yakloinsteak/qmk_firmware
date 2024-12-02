#pragma once

#include QMK_KEYBOARD_H

enum custom_keycodes {
    SNIPPETS = SAFE_RANGE,
    SWITCH_WINDOW,
    MAGIC_QUOTE,
    UPDIR,
    DBLCLK
};

// YL == yakloin
//
// MT == mod-tap (mod if held, tap the keycode otherwise)
#define YL_ESC MT(MOD_LCTL, KC_ESC)

#define YL_RSFT MT(MOD_RSFT, KC_ENT)
