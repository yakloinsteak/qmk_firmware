#include QMK_KEYBOARD_H
#include "mylayers.h"
#include "mykeycodes.h"
#include "combos.h"
#include "hrm.h"
#include "achordion.h"

// Handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }

    /* if (IS_LAYER_ON(TMUX) && record->event.pressed && keycode != MOD_RSFT && keycode != MOD_LSFT) { */
    /*     tap_code16(C(KC_A));  // Tap Ctrl+A. */
    /* } */

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
    }
    return true;
};

// clang-format off
// Key symbols are based on QMK. Use them to remap your keyboard
/*
* Layer BASE
* ,-----------------------------------------------------------------------------------------.
* |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab/FN1|  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | ctrl/esc|  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift/Enter |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  GUI  | TMUX  |               space             |  Alt  |  FN1  |  FN2  |       |
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [BASE] = LAYOUT_60_ansi( /* Base */
    KC_GRV,   KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6,   KC_7, KC_8,    KC_9,    KC_0,             KC_MINS,          KC_EQL,        KC_BSPC,
    YL_TAB,   KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I,    KC_O,    KC_P,             KC_LBRC,          KC_RBRC,       KC_BSLS,
    YL_ESC,   YL_A,    YL_S,    YL_D, YL_F, KC_G, KC_H,   YL_J, YL_K,    YL_L,    YL_SCLN,          KC_QUOT,          KC_ENT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH,          YL_RSFT,
    KC_LCTL,  KC_LGUI, MO(TMUX),                   KC_SPC,       KC_RALT, _______, LT(FN2, KC_DOWN), KC_NO
),
  /*
  * tab hold
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab/UTL|  q  | UP  |  e  |  r  |  t  |  y  |HOME |PGUP |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |LEFT |DOWN | UP  |RIGHT|     |     |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  | END |PGDN |INSRT| DEL |   Shift/Enter  |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  GUI  |  Alt  |               space             |  Alt  |  FN1  |  FN2  | FN3 |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [TAB_HOLD_LAYER] = LAYOUT_60_ansi( /* FN1 */
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, _______, KC_PSCR, _______, KC_BSPC, _______,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_INS,  KC_DEL,  _______,
    _______, _______, _______,                            _______,                   _______, _______, _______, _______
),
  /*
  * Layer FN2
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 | F7 | F8 | MOD | TOG | BRI- | BRI+ |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  GUI  |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [FN2] = LAYOUT_60_ansi( /* FN2 */
    QK_BOOT, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, _______, _______, KC_AP_LED_PREV_PROFILE, KC_AP_LED_NEXT_PROFILE, KC_AP_RGB_TOG, KC_AP_RGB_VAD, KC_AP_RGB_VAI, _______,
    _______, _______,    DT_UP,      _______,    _______,    _______, _______, _______, _______, _______,       KC_PSCR,       KC_HOME,       KC_END,        _______,
    _______, KC_BRID,    DT_DOWN,    KC_BRIU,    _______,    _______, _______, _______, _______, _______,       KC_PGUP,       KC_PGDN,       _______,
    _______, _______,    DT_PRNT,    _______,    _______,    _______, _______, _______, _______, KC_INS,        KC_DEL,        _______,
    _______, _______,    _______,                                     _______,                   _______,       _______,       _______,       _______
 ),
 // KC_BRIU: brightness
 // KC_BRID: brightness
 // DT_xx: adjust and print delay timing

 // mouse that takes up too much ram I think
 /* [FN3] = LAYOUT_60_ansi( */
 /*    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
 /*    XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
 /*    _______, MS_WHLL, MS_WHLD, MS_WHLR, XXXXXXX, XXXXXXX, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX, MS_BTN1, */
 /*    _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
 /*    XXXXXXX, XXXXXXX, XXXXXXX,                                     MS_BTN2,                   XXXXXXX, XXXXXXX, XXXXXXX, _______ */
 /* ), */

 [TMUX] = LAYOUT_60_ansi(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                                     _______,                   _______, _______, _______, _______
 ),

};
// clang-format on

// https://getreuer.info/posts/keyboards/achordion/
void matrix_scan_user(void) {
  achordion_task();
}

uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode, uint16_t next_keycode) {
  return 100;  // Default of 100 ms.
}

// Can customize the hold timing
// 500-5000ms suggested
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  return 300;
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // Exceptions for chords on the same hand
  switch (tap_hold_keycode) {
  case KC_LCTL:
  case YL_ESC:
      // Left ctrl on pinkie and these are muscle-memoried...
      if ((other_keycode == KC_F) || (other_keycode == KC_V) || (other_keycode == KC_C) || (other_keycode == KC_X) || (other_keycode == KC_B)) { return true; }
      // on_left_hand() has an off-by-one bug I think.
      if (other_keycode == KC_H) { return true; }
      break;
  // TODO: AP (should do ap not left-alt-p). figure out what alt-p does anyway. This should return false
  // TODO: ly may need a fix like KC_H above. it sends ^Y but it's the same hand?
  }

  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  // if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 4) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_RSFT:
    case MOD_LCTL:
    case MOD_RCTL:
      return true;  // Eagerly apply Shift and Ctrl mods.

    default:
      return false;
  }
}

// ********************************************************************************************************** //
// ************************************************* Chords ************************************************* //
// ********************************************************************************************************** //

combo_t key_combos[] = {
    COMBO(ctrla_combo, LCTL(KC_A)),  // er: send ^a
    COMBO(snippets_combo, SNIPPETS), // ui: snippets in tmux
    // COMBO(tmux_window_switch_combo, SWITCH_WINDOW), // common switch window
    // COMBO(enter_combo, KC_ENT), // Enter
};


// ******************************************************************************************************** //
// ************************************************* LEDs ************************************************* //
// ******************************************************************************************************** //

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    ap2_led_enable();
    // ap2_led_set_profile(0);

    ap2_led_set_foreground_color(0xAA, 0x00, 0x00);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case TAB_HOLD_LAYER:
            // Set the leds to green
            ap2_led_set_foreground_color(0x00, 0xFF, 0x00);
            break;
        case FN2:
            // Set the leds to blue
            ap2_led_set_foreground_color(0x00, 0x00, 0xFF);
            break;
        case TMUX:
            // Set the leds to
            ap2_led_set_foreground_color(0xFF, 0x00, 0xFF);
            break;
        default:
            // Reset back to the current profile (doesn't work)
            // so set to a specific color for now
            ap2_led_set_foreground_color(0xAA, 0x00, 0x00);
            break;
    }
    return state;
}
#endif

// ******************************************************************************************************** //
// ************************************************* TAPS ************************************************* //
// ******************************************************************************************************** //
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case YL_ESC:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* case SFT_T(KC_SPC): */
        /*     return g_tapping_term + 1250; */
        /* case KC_RSFT: */
        /* case YL_RSFT: */
        /*     return g_tapping_term - 80; */
        /* case YL_ESC: */
        /* case KC_ESC: */
        /* case KC_LCTL: */
        /*     return g_tapping_term - 40; */
        /* case YL_TAB: */
        /* case KC_TAB: */
        /*     return g_tapping_term - 60; */
        default:
            return g_tapping_term;
    }
}
