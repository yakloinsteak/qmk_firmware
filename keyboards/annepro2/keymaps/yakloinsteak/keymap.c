#include QMK_KEYBOARD_H
#include "mylayers.h"
#include "mykeycodes.h"
#include "combos.h"

// Handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(TMUX) && record->event.pressed && keycode != MOD_RSFT && keycode != MOD_LSFT) {
        tap_code16(C(KC_A));  // Tap Ctrl+A.
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
    YL_ESC,   KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K,    KC_L,    KC_SCLN,          KC_QUOT,          KC_ENT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH,          YL_RSFT,
    KC_LCTL,  KC_LGUI, MO(TMUX),                   KC_SPC,       KC_RALT, LT(FN1, KC_LEFT), LT(FN2, KC_DOWN), KC_NO
),
  /*
  * Layer FN1
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
 [FN1] = LAYOUT_60_ansi( /* FN1 */
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
    _______, _______,    DT_PRNT,    _______,    _______,    _______, _______, _______, _______,    KC_INS,        KC_DEL,        _______,
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

// ********************************************************************************************************** //
// ************************************************* Chords ************************************************* //
// ********************************************************************************************************** //

/* const uint16_t PROGMEM ctrla_combo[] = {KC_S, KC_D, COMBO_END}; */
/* const uint16_t PROGMEM tmux_window_switch_combo[] = {KC_A, KC_S, KC_D, KC_F, COMBO_END}; */
/* const uint16_t PROGMEM snippets_combo[] = {KC_K, KC_L, COMBO_END}; */
/* // const uint16_t PROGMEM enter_combo[] = {KC_L, KC_SCLN, COMBO_END}; */
/*  */
/* const uint16_t PROGMEM hrm1l[4][3] = { */
/*     {KC_SPC, KC_F, COMBO_END}, */
/*     {KC_SPC, KC_D, COMBO_END}, */
/*     {KC_SPC, KC_S, COMBO_END}, */
/*     {KC_SPC, KC_A, COMBO_END}, */
/* }; */
/* const uint16_t PROGMEM hrm1r[4][3] = { */
/*     {KC_SPC, KC_J, COMBO_END}, */
/*     {KC_SPC, KC_K, COMBO_END}, */
/*     {KC_SPC, KC_L, COMBO_END}, */
/*     {KC_SPC, KC_SCLN, COMBO_END}, */
/* }; */
/* const uint16_t PROGMEM hrm2l[6][4] = { */
/*     {KC_SPC, KC_F, KC_D, COMBO_END}, */
/*     {KC_SPC, KC_F, KC_S, COMBO_END}, */
/*     {KC_SPC, KC_F, KC_A, COMBO_END}, */
/*     {KC_SPC, KC_D, KC_S, COMBO_END}, */
/*     {KC_SPC, KC_D, KC_A, COMBO_END}, */
/*     {KC_SPC, KC_S, KC_A, COMBO_END} */
/* }; */
/* const uint16_t PROGMEM hrm2r[6][4] = { */
/*     {KC_SPC, KC_J, KC_K, COMBO_END}, */
/*     {KC_SPC, KC_J, KC_L, COMBO_END}, */
/*     {KC_SPC, KC_J, KC_SCLN, COMBO_END}, */
/*     {KC_SPC, KC_K, KC_L, COMBO_END}, */
/*     {KC_SPC, KC_K, KC_SCLN, COMBO_END}, */
/*     {KC_SPC, KC_L, KC_SCLN, COMBO_END} */
/* }; */

combo_t key_combos[] = {
    COMBO(ctrla_combo, LCTL(KC_A)),  // SD send ^a
    COMBO(snippets_combo, SNIPPETS), // snippets in tmux
    COMBO(tmux_window_switch_combo, SWITCH_WINDOW), // common switch window
    // COMBO(enter_combo, KC_ENT), // Enter

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
        case FN1:
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

/* uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) { */
/*     switch (keycode) { */
/*         [> case SFT_T(KC_SPC): <] */
/*         [>     return TAPPING_TERM + 1250; <] */
/*         [> case KC_ESC: <] */
/*         [>     return TAPPING_TERM; <] */
/*         default: */
/*             return TAPPING_TERM; */
/*     } */
/* } */
