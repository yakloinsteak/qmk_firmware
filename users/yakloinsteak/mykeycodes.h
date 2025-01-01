#pragma once

#include QMK_KEYBOARD_H
#include "mylayers.h"

enum custom_keycodes {
    SNIPPETS = SAFE_RANGE,
    SWITCH_WINDOW,
    MAGIC_QUOTE,
    UPDIR,
    DBLCLK,
    YL_CTR,
    YL_WRIT,
};

// YL == yakloin
// MT == mod-tap (mod if held, tap the keycode otherwise)
// OSM == one-shot-mod
// LT == layer-tap

#define YL_ESC MT(MOD_LCTL, KC_ESC)
#define YL_RSFT KC_RSFT
//MT(MOD_RSFT, KC_ENT)
#define YL_TAB LT(TAB_HOLD_LAYER, KC_TAB)
#define RRRRRRR _______

#define YL_F    MT(MOD_LGUI, KC_F)
#define YL_D    MT(MOD_LSFT, KC_D)
#define YL_S    MT(MOD_LCTL, KC_S)
#define YL_A    MT(MOD_LALT, KC_A)

#define YL_J    MT(MOD_RGUI, KC_J)
#define YL_K    MT(MOD_RSFT, KC_K)
#define YL_L    MT(MOD_RCTL, KC_L)
#define YL_SCLN MT(MOD_RALT, KC_SCLN)
#define YL_RUSN KC_APP

// #define ST_LGUI OSM(MOD_LGUI)
// #define ST_LSFT OSM(MOD_LSFT)
// #define ST_LCTL OSM(MOD_LCTL)
// #define ST_LALT OSM(MOD_LALT)
//
// #define ST_RGUI OSM(MOD_RGUI)
// #define ST_RSFT OSM(MOD_RSFT)
// #define ST_RCTL OSM(MOD_RCTL)
// #define ST_RALT OSM(MOD_RALT)
