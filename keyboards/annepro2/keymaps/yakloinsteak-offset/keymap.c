#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"
#include "combos.h"
#include "achordion.h"

#ifdef TAP_DANCE_ENABLE
#  include "tapdance.h"
#endif


// clang-format off
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_60_ansi( /* Base */
    YL_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    YL_ESC,   YL_A,    YL_S,    YL_D,    YL_F,    KC_G,    _______, KC_H,    YL_J,    YL_K,    YL_L,    YL_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, YL_RSFT,
    _______,        _______, _______, YL_LTH3, KC_ENT,  YL_LTH1, YL_RTH1, YL_SPC,  YL_RTH3, _______, _______, _______,
    _______,  _______, _______,                        _______,                                _______, _______, _______, _______
),

[TAB_HOLD_LAYER] = LAYOUT_60_ansi(
    _______,  _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_INS,  KC_PSCR, _______, _______,
    _______,  _______, _______, KC_EQL,  KC_BSLS, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, KC_DEL,  _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, _______, _______, _______,
    _______,        _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______,
    _______,  _______, _______,                            _______,                   _______, _______, _______, _______
 ),

[LOWER] = LAYOUT_60_ansi(
    XXXXXXX,  XXXXXXX, MS_WHLU, XXXXXXX, MS_ACL2, XXXXXXX, XXXXXXX, XXXXXXX, MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______,  MS_WHLL, MS_WHLD, MS_WHLR, MS_ACL0, XXXXXXX, XXXXXXX, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,
    _______,  XXXXXXX, YL_CTR,  MS_ACL1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______,        _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______,
    _______,  _______, _______,                            _______,                   _______, _______, _______, _______
),

 [UPPER] = LAYOUT_60_ansi(
    _______,  _______, _______, KC_EQL,  KC_MINS, _______, _______, _______, KC_PLUS, _______, _______, _______, _______, _______,
    KC_GRV,   YL_1,    YL_2,    YL_3,    YL_4,    KC_5,    _______, KC_6,    YL_7,    YL_8,    YL_9,    YL_0,    _______, _______,
    _______,  YL_BSLS, YL_LT,   YL_LBRC, YL_LCBR, KC_LPRN, _______, KC_RPRN, YL_RCBR, YL_RBRC, YL_GT, YL_SLSH, _______,
    _______,        _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______,
    _______,  _______, _______,                                     _______,                   _______, _______, _______, _______
 ),

 // mirror-pairs
 [ADJUST] = LAYOUT_60_ansi(
    _______, _______, _______, KC_EQL,  KC_MINS, _______, _______, _______, KC_PLUS, _______, _______, _______, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,        _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______,
    _______, _______, _______,                                     _______,                   _______, _______, _______, _______
 ),

 // macros
 [MACROS] = LAYOUT_60_ansi(
    _______, YL_QUIT, YL_WRIT, YL_WSCH, YL_SNIP, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, YL_SSHK, _______, YL_FIAP, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,    LGTM, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                                     _______,                   _______, _______, _______, _______
 ),


 [UTIL] = LAYOUT_60_ansi(
    QK_BOOT, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, _______, _______, KC_AP_LED_PREV_PROFILE, KC_AP_LED_NEXT_PROFILE, KC_AP_RGB_TOG, KC_AP_RGB_VAD, KC_AP_RGB_VAI, _______,
    _______, _______,    DT_UP,      _______,    YL_RUSN,    _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_BRID,    DT_DOWN,    KC_BRIU,    _______,    _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,    DT_PRNT,    _______,    _______,    _______, _______, _______, _______, _______, _______, _______,
    _______, _______,    _______,                                     _______,                   _______, _______, _______, _______
 ),
 // KC_BRIU: brightness
 // KC_BRID: brightness
 // DT_xx: adjust and print delay timing



};
// clang-format on

// ********************************************************************************************************** //
// ************************************************* Chords ************************************************* //
// ********************************************************************************************************** //

/* combo_t key_combos[] = { */
/*     COMBO(snippets_combo, YL_SNIP),           // QE snippets in tmux */
/*     COMBO(ctrla_combo, LCTL(KC_A)),           // QR send ^a */
/*     COMBO(tmux_window_switch_combo, YL_WSCH), // QT open window choice in tmux */
/* }; */

// ******************************************************************************************************** //
// ************************************************* LEDs ************************************************* //
// ******************************************************************************************************** //

void keyboard_post_init_user(void) {
#   ifdef RGB_MATRIX_ENABLE
    ap2_led_enable();
    // ap2_led_set_profile(0);

    ap2_led_set_foreground_color(0xAA, 0x00, 0x00);
#   endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, LOWER, UPPER, ADJUST);

#   ifdef RGB_MATRIX_ENABLE
    switch (get_highest_layer(state)) {
        case TAB_HOLD_LAYER:
            // Set the leds to green
            ap2_led_set_foreground_color(0x00, 0xFF, 0x00);
            break;
        case UTIL:
            // Set the leds to blue
            ap2_led_set_foreground_color(0x00, 0x00, 0xFF);
            break;
        case LOWER:
            // Set the leds to
            ap2_led_set_foreground_color(0xFF, 0x00, 0xFF);
            break;
        case UPPER:
            // Set the leds to
            ap2_led_set_foreground_color(0x1F, 0x00, 0x00);
            break;
        case ADJUST:
            // Set the leds to
            ap2_led_set_foreground_color(0xFF, 0xFF, 0xFF);
            break;
        default:
            // Reset back to the current profile (doesn't work)
            // so set to a specific color for now
            ap2_led_set_foreground_color(0xAA, 0x00, 0x00);
            break;
    }
#   endif

    return state;
}
