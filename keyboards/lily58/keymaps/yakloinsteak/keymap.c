#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"
#include "combos.h"
#include "achordion.h"
#include "tapdance.h"

// *************************************************************************************************** //
// ************************************************* Core ******************************************** //
// *************************************************************************************************** //

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY/Base layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Tb/FN |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  [   | <- tab activates tab-hold layer when held
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ctlesc|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   | <- magic quotes when double tapped
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |shift | <
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      | util | <--- lower/upper layer together is another layer
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[BASE] = LAYOUT(
    YL_GRAV,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    YL_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    YL_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    YL_ESC,   YL_A,   YL_S,    YL_D,    YL_F,    KC_G,                     KC_H,    YL_J,    YL_K,    YL_L,    YL_SCLN, YL_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, YL_RSFT,
                             YL_LTH4, YL_LTH3, KC_ENT, YL_LTH1, YL_RTH1, YL_SPC, YL_RTH3, YL_RTH4
),

/* Tab hold
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  | F9   | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      | home | pgup | ins  | print| F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| left | down |  up  | right|bckspc| del  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | end  | pgdn |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[TAB_HOLD_LAYER] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_HOME, KC_PGUP, KC_INS,  KC_PSCR, KC_F12,
    _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* left thumb layer / mouse */
[LOWER] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX, MS_ACL2, XXXXXXX,                   YL_CTR,  MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, MS_WHLL, MS_WHLD, MS_WHLR, MS_ACL0, XXXXXXX,                   MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, MS_ACL1, XXXXXXX, _______, _______, DBLCLK,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* Right thumb / homerow mod digits and symbols
 * mirror-pairs below homerow
 * */
[UPPER] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_PLUS, _______, _______, _______, _______,
    YL_GRAV, YL_1,    YL_2,    YL_3,    YL_4,    KC_5,                      KC_6,    YL_7,    YL_8,    YL_9,    YL_0,    _______,
    _______, YL_BSLS, YL_LT,   YL_LBRC, YL_LCBR, KC_LPRN, _______, _______, KC_RPRN, YL_RCBR, YL_RBRC, YL_GT,   YL_SLSH, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______
),

// both of closest thumbs together, function keys
[ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_PLUS, _______, _______, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),

// macros, right thumb to the right of home
[MACROS] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, YL_QUIT, YL_WRIT, YL_WSCH, YL_SNIP, _______,                   DM_REC1, DM_REC2, DM_RSTP, _______, _______, _______,
    _______, _______, YL_SSHK, _______, YL_FIAP, _______,                   DM_PLY1, DM_PLY2, UPDIR,   YL_LSTS, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),

// Keyboard/RGB control. bootloader mode. debugging. Screen brightness
// Generally, also, things that you don't type very often or need rarely
// https://docs.qmk.fm/features/rgblight#keycodes
[UTIL] = LAYOUT(
    QK_BOOT, _______, _______, _______, _______, _______,                   UG_TOGG, _______, _______, _______, _______, _______,
    _______, _______, DT_UP  , _______, UC(0x0416), _______,                  _______, _______, _______, _______, _______, _______,
    _______, KC_BRID, DT_DOWN, KC_BRIU, _______, _______,                   UG_PREV, UG_VALD, UG_VALU, UG_NEXT, _______, _______,
    _______, _______, DT_PRNT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

[SYMBOLS] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, KC_PLUS, KC_UNDS, _______,                   _______, _______, _______, _______, _______, _______,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_PIPE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* [] = LAYOUT( */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
/*                              _______, _______, _______, _______, _______, _______, _______, _______ */
/* ), */


};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, LOWER, UPPER, ADJUST);
  state = update_tri_layer_state(state, LOWER, MACROS, UTIL);
  return state;
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if right side
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *yl_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
//const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

// 128x32?
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    // oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
    //oled_write(yl_logo(), false);
    //yl_logo();
  }
  return false;
}
#endif // OLED_ENABLE
