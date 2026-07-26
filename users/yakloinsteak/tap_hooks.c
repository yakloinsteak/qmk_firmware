#include QMK_KEYBOARD_H
#include "mykeycodes.h"

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case YL_ESC: // Rolls should always be okay since not every part of a word?
        case YL_TAB: // Rolls should always be okay since not every part of a word?
        case YL_8: // partial fix for 8- instead of _
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
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

// Chordal Hold's default rule only lets a mod-tap HOLD when the next key is on the
// oppsite hand, so stacking two same-hand home-row mods (e.g. A+S -> Alt+Ctrl for
// copyq, or S+D -> Ctrl+Shift) collapsed the first mod into a tap and leaked a bare
// Ctrl+Alt (which Parallels grabs as its VM-release chord). Achordion allowed such
// same-hand mod stacking; restore it by permitting a hold whenever BOTH keys are
// mod-taps. Fast same-hand *letter* rolls are still guarded by Flow Tap, and non-mod
// chors still follow the default opposite-hands rule.
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                      uint16_t other_keycode, keyrecord_t *other_record) {
    if (IS_QK_MOD_TAP(tap_hold_keycode) && IS_QK_MOD_TAP(other_keycode)) {
        return true;  // allow stacking modifiers, even on the same hand

    // This with HOLD_ON_OTHER_KEY_PRESS_PER_KEY on YL_D allows the d' roll
    // to yield a quote while keeping di (for example) from becoming capital I
    /* } else if (tap_hold_keycode == YL_D && other_keycode != YL_QUOT) { */
    /*     return false; */
    /* } else if (tap_hold_keycode == YL_8 && other_keycode != KC_MINS) { */
    /*     return false; */
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case YL_A:
            return g_tapping_term;
        case YL_S:
            return g_tapping_term - 10;
        case YL_D:
            return g_tapping_term - 75;
        case YL_F:
            return g_tapping_term;
        case YL_J:
            return g_tapping_term;
        case YL_K:
            // Was getting kl when I wanted ctrl-shift for ctrl-shift-v
            return g_tapping_term - 20;
        case YL_L:
            // Was getting kl when I wanted ctrl-shift for ctrl-shift-v
            return g_tapping_term - 20;
        case YL_SCLN:
            return g_tapping_term;
        case YL_TAB:
            return g_tapping_term;
        // Very long hold while I decide what to do with these
        // probably should be very deliberate and/or rare actions?
        case YL_ESC:
        case YL_SPC:
            return g_tapping_term + 150;
        default:
            return g_tapping_term;
    }
}
