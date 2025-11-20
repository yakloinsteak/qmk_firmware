#include QMK_KEYBOARD_H
#include "mykeycodes.h"

// TODO: maybe the shift/return mod tap would benefit?
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return true;

    /* switch (keycode) { */
    /*     case KC_ESC: */
    /*     case YL_ESC: */
    /*         // Immediately select the hold action when another key is pressed. */
    /*         return true; */
    /*     default: */
    /*         // Do not select the hold action when another key is pressed. */
    /*         return false; */
    /* } */
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case YL_A:
            return g_tapping_term;
        case YL_S:
            return g_tapping_term;
        case YL_D:
            return g_tapping_term - 5;
        case YL_F:
            return g_tapping_term;

        case YL_J:
            return g_tapping_term;
        case YL_K:
            return g_tapping_term - 5;
        case YL_L:
            // Was getting kl when I wanted ctrl-shift for ctrl-shift-v
            return g_tapping_term - 5;
        case YL_SCLN:
            return g_tapping_term;

        /* case YL_TAB: */
        case YL_ESC:
            // This key is mostly just esc, but if you hold it a long time, you can activate the hold action
            return g_tapping_term + 30;
        case YL_SPC:
            return g_tapping_term - 40;
        default:
            return g_tapping_term;
    }
}
