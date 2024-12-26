#include "achordion.h"
#include "mykeycodes.h"

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
