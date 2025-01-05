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
// MO == momentary layer

#define YL_ESC MT(MOD_LCTL, KC_ESC)
#define YL_RSFT KC_RSFT
//MT(MOD_RSFT, KC_ENT)
#define YL_TAB LT(TAB_HOLD_LAYER, KC_TAB)
#define RRRRRRR _______
#define YL_RUSN KC_APP

/* Homerow mods */
#define YL_F    MT(MOD_LGUI, KC_F)
#define YL_D    MT(MOD_LSFT, KC_D)
#define YL_S    MT(MOD_LCTL, KC_S)
#define YL_A    MT(MOD_LALT, KC_A)

#define YL_J    MT(MOD_RGUI, KC_J)
#define YL_K    MT(MOD_RSFT, KC_K)
#define YL_L    MT(MOD_RCTL, KC_L)
#define YL_SCLN MT(MOD_RALT, KC_SCLN)

/* Homerow mods for number layer */
#define YL_1    MT(MOD_LGUI, KC_1)
#define YL_2    MT(MOD_LSFT, KC_2)
#define YL_3    MT(MOD_LCTL, KC_3)
#define YL_4    MT(MOD_LALT, KC_4)

#define YL_7    MT(MOD_RGUI, KC_7)
#define YL_8    MT(MOD_RSFT, KC_8)
#define YL_9    MT(MOD_RCTL, KC_9)
#define YL_0    MT(MOD_RALT, KC_0)


/* Thumbs */
#define YL_LTH4 TG(UTIL2)
#define YL_LTH3 MO(U1)
// resting key is enter
#define YL_LTH1 MO(LOWER)

#define YL_RTH1 MO(UPPER)
// Resting key if space
#define YL_RTH3 MO(U2)
#define YL_RTH4 TG(UTIL)

// #define ST_LGUI OSM(MOD_LGUI)
// #define ST_LSFT OSM(MOD_LSFT)
// #define ST_LCTL OSM(MOD_LCTL)
// #define ST_LALT OSM(MOD_LALT)
//
// #define ST_RGUI OSM(MOD_RGUI)
// #define ST_RSFT OSM(MOD_RSFT)
// #define ST_RCTL OSM(MOD_RCTL)
// #define ST_RALT OSM(MOD_RALT)
