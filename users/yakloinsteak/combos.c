#include QMK_KEYBOARD_H
#include "mykeycodes.h"

const uint16_t PROGMEM ctrla_combo[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM snippets_combo[] = {KC_U, KC_I, COMBO_END};
//const uint16_t PROGMEM tmux_window_switch_combo[] = {KC_A, KC_S, KC_D, KC_F, COMBO_END};

#ifdef HRM_CHORD
#   define LTHUMB KC_BSPC
#   define RTHUMB KC_SPC
    const uint16_t PROGMEM hrm1l[4][3] = {
        {LTHUMB, KC_F, COMBO_END},
        {LTHUMB, KC_D, COMBO_END},
        {LTHUMB, KC_S, COMBO_END},
        {LTHUMB, KC_A, COMBO_END},
    };
    const uint16_t PROGMEM hrm1r[4][3] = {
        {RTHUMB, KC_J, COMBO_END},
        {RTHUMB, KC_K, COMBO_END},
        {RTHUMB, KC_L, COMBO_END},
        {RTHUMB, KC_SCLN, COMBO_END},
    };
    const uint16_t PROGMEM hrm2l[6][4] = {
        {LTHUMB, KC_F, KC_D, COMBO_END},
        {LTHUMB, KC_F, KC_S, COMBO_END},
        {LTHUMB, KC_F, KC_A, COMBO_END},
        {LTHUMB, KC_D, KC_S, COMBO_END},
        {LTHUMB, KC_D, KC_A, COMBO_END},
        {LTHUMB, KC_S, KC_A, COMBO_END}
    };
    const uint16_t PROGMEM hrm2r[6][4] = {
        {RTHUMB, KC_J, KC_K, COMBO_END},
        {RTHUMB, KC_J, KC_L, COMBO_END},
        {RTHUMB, KC_J, KC_SCLN, COMBO_END},
        {RTHUMB, KC_K, KC_L, COMBO_END},
        {RTHUMB, KC_K, KC_SCLN, COMBO_END},
        {RTHUMB, KC_L, KC_SCLN, COMBO_END}
    };
#endif
