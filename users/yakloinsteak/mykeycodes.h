#pragma once

#include QMK_KEYBOARD_H
#include "mylayers.h"

enum custom_keycodes {
    YL_SNIP = SAFE_RANGE,
    YL_WSCH,
    UPDIR,
    DBLCLK,
    YL_CTR,
    YL_WRIT,
    YL_QUIT,
    YL_SLSH,
    YL_LT,
    YL_LBRC,
    YL_LCBR,
    YL_RCBR,
    YL_RBRC,
    YL_GT,
    YL_BSLS,
    YL_CTLA,
    YL_BACK,
    YL_FIAP, // firefox insecure approve
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
#define YL_A    MT(MOD_LALT, KC_A)
#define YL_S    MT(MOD_LCTL, KC_S)
#define YL_D    MT(MOD_LSFT, KC_D)
#define YL_F    MT(MOD_LGUI, KC_F)

#define YL_J    MT(MOD_RGUI, KC_J)
#define YL_K    MT(MOD_RSFT, KC_K)
#define YL_L    MT(MOD_RCTL, KC_L)
#define YL_SCLN MT(MOD_RALT, KC_SCLN)

/* Homerow mods for number layer */
#define YL_1    MT(MOD_LALT, KC_1)
#define YL_2    MT(MOD_LCTL, KC_2)
#define YL_3    MT(MOD_LSFT, KC_3)
#define YL_4    MT(MOD_LGUI, KC_4)

#define YL_7    MT(MOD_RGUI, KC_7)
#define YL_8    MT(MOD_RSFT, KC_8)
#define YL_9    MT(MOD_RCTL, KC_9)
#define YL_0    MT(MOD_RALT, KC_0)

/* Homerow mods for pairs layer */
#define YL_SLSH MT(MOD_LALT, YL_SLSH)
#define YL_LT   MT(MOD_LCTL, YL_LT)
#define YL_LBRC MT(MOD_LSFT, YL_LBRC)
#define YL_LCBR MT(MOD_LGUI, YL_LCBR)

#define YL_RCBR MT(MOD_RGUI, YL_RCBR)
#define YL_RBRC MT(MOD_RSFT, YL_RBRC)
#define YL_GT   MT(MOD_RCTL, YL_GT)
#define YL_BSLS MT(MOD_RALT, YL_BSLS)

/* Thumbs */
//#define YL_LTH4 TG(UTIL2)
#define YL_LTH4 YL_BACK

//#define YL_LTH3 MO(U1)
#define YL_LTH3 YL_CTLA
//#define YL_LTH3 LT(U1, YL_CTLA)

// resting key is enter
#define YL_LTH1 MO(LOWER)

#define YL_RTH1 MO(UPPER)
// Resting key if space
#define YL_RTH3 MO(U2)
#define YL_RTH4 TG(UTIL)
