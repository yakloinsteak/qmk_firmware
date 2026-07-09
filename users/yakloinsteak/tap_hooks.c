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

// Flow Tap decides at keydown based on the *previous* key, so when typing fast it
// forces a home-row mod to tap before you get to press the next key. That breaks the
// deliberate "hold Shift, then tap a symbol" roll (e.g. YL_D + . -> >), which the old
// Achordion streak allowed because it looked *forward* at the next key instead.
//
// Mirror the old carve-out: exempt only the two home-row SHIFT mod-taps from Flow Tap,
// letting Chordal Hold + Permissive Hold settle them by nested-vs-rolled timing (a
// deliberate hold keeps the key down through the symbol tap; a fast roll releases it
// first). Ctrl/Alt/GUI mods keep full Flow Tap protection so fast rolls never fire a
// shortcut.
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    switch (keycode) {
        case YL_D:   // home-row Shift (left hand)
        case YL_K:   // home-row Shift (right hand)
            return 0;  // never let Flow Tap force these to tap
    }
    // Default behavior for every other key.
    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }
    return 0;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case YL_A:
            return g_tapping_term;
        case YL_S:
            return g_tapping_term;
        case YL_D:
            return g_tapping_term - 20;
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
            return g_tapping_term - 55;
        default:
            return g_tapping_term;
    }
}
