#include QMK_KEYBOARD_H
#include "mykeycodes.h"

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
