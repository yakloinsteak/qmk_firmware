#include QMK_KEYBOARD_H
#include "mykeycodes.h"

// TODO: maybe the shift/return mod tap would benefit if I bring that back?
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
