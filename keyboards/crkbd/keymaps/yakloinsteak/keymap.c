#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"
#include "combos.h"
#include "achordion.h"
#include "tapdance.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_split_3x6_3(
    YL_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    YL_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    YL_ESC,   YL_A,   YL_S,    YL_D,    YL_F,    KC_G,                     KC_H,    YL_J,    YL_K,    YL_L,    YL_SCLN, YL_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, YL_RSFT,
                                   YL_LTH3, KC_ENT, YL_LTH1,        YL_RTH1, YL_SPC, YL_RTH3
),

[TAB_HOLD_LAYER] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_HOME, KC_PGUP, KC_INS,  KC_PSCR, KC_F12,
    _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, KC_DEL,
    _______, _______, _______, _______, _______, _______,                   _______, KC_END,  KC_PGDN, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

/* left thumb layer / mouse */
[LOWER] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX, MS_ACL2, XXXXXXX,                   YL_CTR,  MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, MS_WHLL, MS_WHLD, MS_WHLR, MS_ACL0, XXXXXXX,                   MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, MS_ACL1, XXXXXXX,                   DBLCLK,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______,                   _______, _______, _______
),

/* Right thumb / homerow mod digits and symbols
 * mirror-pairs below homerow
 * */
[UPPER] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_PLUS, _______, _______, _______, _______,
    YL_GRAV, YL_1,    YL_2,    YL_3,    YL_4,    KC_5,                      KC_6,    YL_7,    YL_8,    YL_9,    YL_0,    _______,
    _______, YL_BSLS, YL_LT,   YL_LBRC, YL_LCBR, KC_LPRN,                   KC_RPRN, YL_RCBR, YL_RBRC, YL_GT,   YL_SLSH, _______,
                               _______, _______, _______,                   _______, _______, _______
),

// both of closest thumbs together, function keys
[ADJUST] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_PLUS, _______, _______, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

// macros, right thumb to the right of home
[MACROS] = LAYOUT_split_3x6_3(
  _______, YL_QUIT, YL_WRIT, YL_WSCH, YL_SNIP, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, YL_SSHK, _______, YL_FIAP, _______,                   _______, _______, UPDIR,   YL_LSTS, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                             _______, _______, _______,                   _______, _______, _______
),

// Keyboard/RGB control. bootloader mode. debugging. Screen brightness
// Generally, also, things that you don't type very often or need rarely
// https://docs.qmk.fm/features/rgblight#keycodes
[UTIL] = LAYOUT_split_3x6_3(
    QK_BOOT, _______, DT_UP  , _______, _______, _______,                   _______, RM_TOGG, _______, _______, _______, _______,
    _______, KC_BRID, DT_DOWN, KC_BRIU, _______, _______,                   RM_SATD, RM_PREV, RM_NEXT, RM_SATU, _______, _______,
    _______, _______, DT_PRNT, _______, _______, _______,                   RM_VALD, RM_HUED, RM_HUEU, RM_VALU, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

[SYMBOLS] = LAYOUT_split_3x6_3(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

/* [LED] = LAYOUT_split_3x6_3( */
/*     _______, _______, _______, _______, _______, _______,                   RM_VALD, UG_VALD, UG_VALU, RM_VALU, _______, _______, */
/*     _______, _______, _______, _______, _______, _______,                   RM_PREV, UG_PREV, UG_NEXT, RM_NEXT, _______, _______, */
/*     _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*                                _______, _______, _______,                   _______, _______, _______ */
/* ), */
  /*   [3] = LAYOUT_split_3x6_3( */
  /* //,-----------------------------------------------------.                    ,-----------------------------------------------------. */
  /*     QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
  /* //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
  /*     RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
  /* //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
  /*     RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
  /* //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
  /*                                         KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT */
  /*                                     //`--------------------------'  `--------------------------' */
  /* ) */
};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, LOWER, UPPER, ADJUST);
  state = update_tri_layer_state(state, LOWER, MACROS, UTIL);
  return state;
}
