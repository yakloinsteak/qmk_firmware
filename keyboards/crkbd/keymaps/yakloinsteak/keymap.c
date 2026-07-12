#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"
#include "combos.h"
#ifdef TAP_DANCE_ENABLE
#include "tapdance.h"
#endif
#include "mymouse.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_split_3x6_3(
    YL_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    YL_CRPT,
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

/* left thumb layer right of home / mouse */
[LTHUMB_2R] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX, MS_ACL2, XXXXXXX,                   YL_WRPB, MS_BTN1, MS_BTN2, XXXXXXX, YL_WRPL, XXXXXXX,
    _______, MS_WHLL, MS_WHLD, MS_WHLR, MS_ACL0, XXXXXXX,                   MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, YL_WRPC, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, MS_ACL1, XXXXXXX,                   DBLCLK,  XXXXXXX, XXXXXXX, XXXXXXX, YL_WRPR, XXXXXXX,
                               _______, _______, _______,                   _______, _______, _______
),

/* Right thumb left of home / homerow mod digits and symbols
 * mirror-pairs below homerow
 * */
[RTHUMB_2L] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_PLUS, _______, _______, _______, _______,
    YL_GRAV, YL_1,    YL_2,    YL_3,    YL_4,    KC_5,                      KC_6,    YL_7,    YL_8,    YL_9,    YL_0,    _______,
    _______, YL_BSLS, YL_LT,   YL_LBRC, YL_LCBR, KC_LPRN,                   KC_RPRN, YL_RCBR, YL_RBRC, YL_GT,   YL_SLSH, _______,
                               _______, YL_ENT, _______,                    _______, _______, _______
),

// both of closest thumbs moved together inward from home, function keys
[THUMBS_INWARD] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_PLUS, _______, _______, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

// macros, right thumb to the right of home
[MACROS] = LAYOUT_split_3x6_3(
    _______, YL_QUIT, YL_WRIT, YL_WSCH, YL_SNIP, _______,                   DM_REC1, DM_REC2, DM_RSTP, _______, _______, _______,
    _______, _______, YL_SSHK, _______, YL_FIAP, _______,                   DM_PLY1, DM_PLY2, UPDIR,   YL_LSTS, _______, _______,
    _______, _______, _______, _______,    LGTM, _______,                   _______, _______, _______, _______, _______, _______,
                               _______,  YL_ENT, _______,                   _______, _______, _______
),

// Keyboard/RGB control. bootloader mode. debugging. Screen brightness
// Generally, also, things that you don't type very often or need rarely
// https://docs.qmk.fm/features/rgblight#keycodes
[UTIL] = LAYOUT_split_3x6_3(
    QK_BOOT, _______, DT_UP  , _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, DT_DOWN, DB_TOGG, _______, _______,                   _______, YL_MON1, YL_MON2, YL_MON3, _______, _______,
    _______, _______, DT_PRNT, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

// thumbs outward and together
[SYMBOLS] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_PLUS, KC_UNDS, _______,                   _______, _______, _______, _______, _______, _______,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_PIPE, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, YL_ENT,  _______,                   _______, _______, _______
),

// Per-key mouse warp. Entered one-shot via YL_CRPT (OSL(WARP)) on the top-right
// key. Every alpha key warps the cursor to the desktop point mirroring its
// physical spot; targets live in warp_frac below. Thumbs stay transparent.
[WARP] = LAYOUT_split_3x6_3(
    YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP,                   YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP,
    YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP,                   YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP,
    YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP,                   YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP, YL_WARP,
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

// WARP-layer targets, authored in physical key order via the same LAYOUT macro
// so QMK maps each to its matrix cell. WF(col, row): col 0..11 -> horizontal
// fraction col/11, row 0..2 (top/home/bottom) -> vertical fraction row/2, each
// scaled to 0..255 and packed (fx<<8 | fy). Non-alpha cells hold 0 (never read;
// YL_WARP is only placed on the alpha keys). See yl_warp_target in mymouse.c.
#define WF(c, r) (uint16_t)((((uint32_t)(c) * 255 / 11) << 8) | ((uint32_t)(r) * 255 / 2))
static const uint16_t warp_frac[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_split_3x6_3(
    WF(0,0), WF(1,0), WF(2,0), WF(3,0), WF(4,0), WF(5,0),                   WF(6,0), WF(7,0), WF(8,0), WF(9,0), WF(10,0), WF(11,0),
    WF(0,1), WF(1,1), WF(2,1), WF(3,1), WF(4,1), WF(5,1),                   WF(6,1), WF(7,1), WF(8,1), WF(9,1), WF(10,1), WF(11,1),
    WF(0,2), WF(1,2), WF(2,2), WF(3,2), WF(4,2), WF(5,2),                   WF(6,2), WF(7,2), WF(8,2), WF(9,2), WF(10,2), WF(11,2),
                                    0, 0, 0,                                     0, 0, 0
);
#undef WF

uint16_t yl_warp_target(uint8_t row, uint8_t col) { return warp_frac[row][col]; }

// OLED rendering is shared across boards in users/yakloinsteak/myoled.c.
