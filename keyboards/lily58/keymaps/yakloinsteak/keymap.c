#include QMK_KEYBOARD_H
#include "mykeycodes.h"

enum layer_number {
    BASE = 0,
    SYM,  // symbols
    UTIL, // Utility/misc.
    MS,   // Mouse
};

// ********************************************************************************************************** //
// ************************************************* Tap Dancing ******************************************** //
// ********************************************************************************************************** //

enum {
  TD_QUOT,
};

// https://docs.qmk.fm/features/tap_dance#how-to-use
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ', twice for two quotes and a backspace
    [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, MAGIC_QUOTE),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ctlesc|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   | <- magic quotes when double tapped
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |sh/ent| <- right shift act as enter
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |MOUSE |  SYM | UTIL | /?????? /       \Space \  | UTIL |  SYM | RGUI |
 *                   |TOGGLE|      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [BASE] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  YL_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, TD_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, YL_RSFT,
                        TG(MS), MO(SYM), MO(UTIL), KC_SPC,  KC_SPC, MO(UTIL), MO(SYM), KC_RGUI
),
/* SYMBOLS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   ~  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[SYM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* UTILITY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[UTIL] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
/* MOUSE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [MS] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, MS_WHLL, MS_WHLD, MS_WHLR, XXXXXXX, XXXXXXX,                   MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, MS_BTN1, MS_BTN2,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, SYM, UTIL, MS);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
      set_keylog(keycode, record);
#endif
      // set_timelog();
    }

    switch (keycode) {
    case SNIPPETS:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"Z"SS_DELAY(100)"snippets"SS_TAP(X_ENT));
        }
        break;

    case SWITCH_WINDOW:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"s");
        }
        break;

    case MAGIC_QUOTE:
        if (record->event.pressed) {
            if ( (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT))) {
               SEND_STRING("\"\"\b");
            } else {
               SEND_STRING("''\b");
            }
        }
        break;

    }


  return true;
}


// ********************************************************************************************************** //
// ************************************************* Chords ************************************************* //
// ********************************************************************************************************** //

const uint16_t PROGMEM ctrla_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM tmux_window_switch_combo[] = {KC_A, KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM snippets_combo[] = {KC_K, KC_L, COMBO_END};

const uint16_t PROGMEM hrm1l[4][3] = {
    {KC_SPC, KC_F, COMBO_END},
    {KC_SPC, KC_D, COMBO_END},
    {KC_SPC, KC_S, COMBO_END},
    {KC_SPC, KC_A, COMBO_END},
};
const uint16_t PROGMEM hrm1r[4][3] = {
    {KC_SPC, KC_J, COMBO_END},
    {KC_SPC, KC_K, COMBO_END},
    {KC_SPC, KC_L, COMBO_END},
    {KC_SPC, KC_SCLN, COMBO_END},
};
const uint16_t PROGMEM hrm2l[6][4] = {
    {KC_SPC, KC_F, KC_D, COMBO_END},
    {KC_SPC, KC_F, KC_S, COMBO_END},
    {KC_SPC, KC_F, KC_A, COMBO_END},
    {KC_SPC, KC_D, KC_S, COMBO_END},
    {KC_SPC, KC_D, KC_A, COMBO_END},
    {KC_SPC, KC_S, KC_A, COMBO_END}
};
const uint16_t PROGMEM hrm2r[6][4] = {
    {KC_SPC, KC_J, KC_K, COMBO_END},
    {KC_SPC, KC_J, KC_L, COMBO_END},
    {KC_SPC, KC_J, KC_SCLN, COMBO_END},
    {KC_SPC, KC_K, KC_L, COMBO_END},
    {KC_SPC, KC_K, KC_SCLN, COMBO_END},
    {KC_SPC, KC_L, KC_SCLN, COMBO_END}
};

combo_t key_combos[] = {
    COMBO(ctrla_combo, LCTL(KC_A)),  // SD send ^a
    COMBO(snippets_combo, SNIPPETS), // snippets in tmux
    COMBO(tmux_window_switch_combo, SWITCH_WINDOW), // common switch window

    // Single mods
    COMBO(hrm1l[0], KC_LGUI),
    COMBO(hrm1l[1], KC_LSFT),
    COMBO(hrm1l[2], KC_LCTL),
    COMBO(hrm1l[3], KC_LALT),
    COMBO(hrm1r[0], KC_RGUI),
    COMBO(hrm1r[1], KC_RSFT),
    COMBO(hrm1r[2], KC_RCTL),
    COMBO(hrm1r[3], KC_RALT),

    // Dual mods
    COMBO(hrm2l[0], G(KC_LSFT)),
    COMBO(hrm2l[1], G(KC_LCTL)),
    COMBO(hrm2l[2], G(KC_LALT)),
    COMBO(hrm2l[3], S(KC_LCTL)),
    COMBO(hrm2l[4], S(KC_LALT)),
    COMBO(hrm2l[5], C(KC_LALT)),
    COMBO(hrm2r[0], G(KC_RSFT)),
    COMBO(hrm2r[1], G(KC_RCTL)),
    COMBO(hrm2r[2], G(KC_RALT)),
    COMBO(hrm2r[3], S(KC_RCTL)),
    COMBO(hrm2r[4], S(KC_RALT)),
    COMBO(hrm2r[5], C(KC_RALT))
};

