#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"
#include "combos.h"
#ifdef TAP_DANCE_ENABLE
#include "tapdance.h"
#endif
#include "mymouse.h"

// Kinesis Advantage (kinT family). The alpha block is the same 3x12 shape as the
// crkbd, so the alpha/thumb assignments mirror keyboards/crkbd/keymaps/yakloinsteak
// key for key. What the crkbd does not have — a function row, a dedicated number
// row and the small outboard bottom row — carries the stock Kinesis legends.
//
// Scroll Lock locks stock-Kinesis mode (KINESIS); Keypad toggles the stock numpad.
//
// Thumb clusters, inner to outer: the small inner column, the inner large key,
// the outer large key. That maps onto the crkbd's three thumbs in the same order.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  TG(KINESIS), KC_PAUS, TG(KEYPAD), QK_BOOT,
    KC_EQL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
    YL_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     YL_CRPT,
    YL_ESC,   YL_A,     YL_S,     YL_D,     YL_F,     KC_G,                                                                      KC_H,     YL_J,     YL_K,     YL_L,     YL_SCLN,  YL_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  YL_RSFT,
              YL_GRAV,  KC_INS,   KC_LEFT,  YL_LTH3,                                                                                       YL_RTH3,  KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LCTL,  KC_LALT,                                               KC_RGUI,  KC_RCTL,
                                                                YL_LTH4,                                               YL_RTH4,
                                            KC_ENT,  YL_LTH1,   YL_LTH4,                                               YL_RTH4,  YL_RTH1,   YL_SPC
),

[TAB_HOLD_LAYER] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  KC_EQL,   KC_MINS,  _______,                                                                   _______,  KC_HOME,  KC_PGUP,  KC_INS,   KC_PSCR,  KC_F12,
    _______,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_LGUI,  _______,                                                                   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_BSPC,  KC_DEL,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  KC_END,   KC_PGDN,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  _______,  _______,                                               _______,  _______,  _______
),

/* left thumb layer right of home / mouse */
[LTHUMB_2R] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    XXXXXXX,  XXXXXXX,  MS_WHLU,  XXXXXXX,  MS_ACL2,  XXXXXXX,                                                                   YL_WRPB,  MS_BTN1,  MS_BTN2,  XXXXXXX,  YL_WRPL,  XXXXXXX,
    _______,  MS_WHLL,  MS_WHLD,  MS_WHLR,  MS_ACL0,  XXXXXXX,                                                                   MS_LEFT,  MS_DOWN,  MS_UP,    MS_RGHT,  YL_WRPC,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MS_ACL1,  XXXXXXX,                                                                   DBLCLK,   XXXXXXX,  XXXXXXX,  XXXXXXX,  YL_WRPR,  XXXXXXX,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  _______,  _______,                                               _______,  _______,  _______
),

/* Right thumb left of home / homerow mod digits and symbols
 * mirror-pairs below homerow
 */
[RTHUMB_2L] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  KC_EQL,   KC_MINS,  _______,                                                                   _______,  KC_PLUS,  _______,  _______,  _______,  _______,
    YL_GRAV,  YL_1,     YL_2,     YL_3,     YL_4,     KC_5,                                                                      KC_6,     YL_7,     YL_8,     YL_9,     YL_0,     _______,
    _______,  YL_BSLS,  YL_LT,    YL_LBRC,  YL_LCBR,  KC_LPRN,                                                                   KC_RPRN,  YL_RCBR,  YL_RBRC,  YL_GT,    YL_SLSH,  _______,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  YL_ENT,   _______,                                               _______,  _______,  _______
),

// both of the closest thumbs moved outward from home, function keys
[THUMBS_OUTWARD] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  KC_EQL,   KC_MINS,  _______,                                                                   _______,  KC_PLUS,  _______,  _______,  _______,  _______,
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                                                                     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
    _______,  KC_F11,   KC_F12,   KC_F13,   KC_F14,   KC_F15,                                                                    KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  _______,  _______,                                               _______,  _______,  _______
),

// macros, right thumb to the right of home
[MACROS] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  YL_QUIT,  YL_WRIT,  YL_WSCH,  YL_SNIP,  _______,                                                                   DM_REC1,  DM_REC2,  DM_RSTP,  _______,  _______,  _______,
    _______,  _______,  YL_SSHK,  _______,  _______,  _______,                                                                   DM_PLY1,  DM_PLY2,  UPDIR,    YL_LSTS,  _______,  _______,
    _______,  _______,  _______,  _______,  LGTM,     _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  YL_ENT,   _______,                                               _______,  _______,  _______
),

// Keyboard control, bootloader, debugging, monitor layout. Things typed rarely.
[UTIL] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    QK_BOOT,  _______,  DT_UP,    _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  DT_DOWN,  DB_TOGG,  _______,  _______,                                                                   _______,  YL_MON1,  YL_MON2,  YL_MON3,  _______,  _______,
    _______,  _______,  DT_PRNT,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  _______,  _______,                                               _______,  _______,  _______
),

// thumbs together
[THUMBS_INWARD] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  KC_PLUS,  KC_UNDS,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                                                                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
    _______,  KC_PIPE,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  YL_ENT,   _______,                                               _______,  _______,  _______
),

// Per-key mouse warp, entered one-shot via YL_CRPT. Alphas only; see warp_frac.
[WARP] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,                                                                   YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,
    YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,                                                                   YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,
    YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,                                                                   YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,  YL_WARP,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  _______,  _______,                                               _______,  _______,  _______
),

[ESC_HOLD_LAYER] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  _______,  _______,                                               _______,  _______,  _______
),

[SPC_HOLD_LAYER] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  _______,  _______,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  _______,  _______,                                               _______,  _______,  _______
),

// Stock Kinesis (keymaps/default QWERTY) for anyone else at the keyboard. No combos (mylayers.c).
[KINESIS] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  TO(BASE), KC_PAUS,  TG(KEYPAD), QK_BOOT,
    KC_EQL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                                                      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_GRV,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LCTL,  KC_LALT,                                               KC_RGUI,  KC_RCTL,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  KC_ENTER, KC_SPC
),

// Stock embedded keypad, over either mode.
// ponytail: right-hand numpad only; add F-row/left-hand keypad legends once checked against the keycaps.
[KEYPAD] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  KC_NUM,   KC_PEQL,  KC_PSLS,  KC_PAST,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                                                                   _______,  KC_P1,    KC_P2,    KC_P3,    KC_PENT,  _______,
              _______,  _______,  _______,  _______,                                                                                       _______,  _______,  KC_PDOT,  KC_PENT,
                                                      _______,  _______,                                               _______,  _______,
                                                                _______,                                               _______,
                                            _______,  _______,  _______,                                               _______,  _______,  KC_P0
),

};

// WARP-layer targets, authored in physical key order via the same LAYOUT macro
// so QMK maps each to its matrix cell. WF(col, row): col 0..11 -> horizontal
// fraction col/11, row 0..2 (top/home/bottom of the alpha block) -> vertical
// fraction row/2, each scaled to 0..255 and packed (fx<<8 | fy). Non-alpha cells
// hold 0 (never read; YL_WARP is only placed on the alphas).
#define WF(c, r) (uint16_t)((((uint32_t)(c) * 255 / 11) << 8) | ((uint32_t)(r) * 255 / 2))
static const uint16_t warp_frac[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,                                                        0, 0, 0, 0, 0, 0,
    WF(0,0), WF(1,0), WF(2,0), WF(3,0), WF(4,0), WF(5,0),                    WF(6,0), WF(7,0), WF(8,0), WF(9,0), WF(10,0), WF(11,0),
    WF(0,1), WF(1,1), WF(2,1), WF(3,1), WF(4,1), WF(5,1),                    WF(6,1), WF(7,1), WF(8,1), WF(9,1), WF(10,1), WF(11,1),
    WF(0,2), WF(1,2), WF(2,2), WF(3,2), WF(4,2), WF(5,2),                    WF(6,2), WF(7,2), WF(8,2), WF(9,2), WF(10,2), WF(11,2),
             0, 0, 0, 0,                                                              0, 0, 0, 0,
                                       0, 0,                                 0, 0,
                                          0,                                 0,
                                    0, 0, 0,                                 0, 0, 0
);
#undef WF

uint16_t yl_warp_target(uint8_t row, uint8_t col) { return warp_frac[row][col]; }
