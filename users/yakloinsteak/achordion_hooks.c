#include "achordion.h"
#include "mykeycodes.h"

// https://getreuer.info/posts/keyboards/achordion/
void matrix_scan_user(void) {
    achordion_task();
}

uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode, uint16_t next_keycode) {
    // Streak-suppression exists to stop *accidental* mods during fast LETTER
    // typing (rolling "do" shouldn't yield "dO"). But rolling a home-row SHIFT
    // into a symbol is intentional (D+" -> ", 8+- -> _); the streak guard is
    // what turns those into the tap+tap garbage "d'" / "8-".
    //
    // Relax the streak only for SHIFT mod-taps (leave Ctrl/Alt/GUI alone so a
    // fast roll never fires a shortcut), and only when the next key is not a
    // normal "wordy" key (letter / space / . / ,).
    if (IS_QK_MOD_TAP(tap_hold_keycode) &&
        (QK_MOD_TAP_GET_MODS(tap_hold_keycode) & MOD_LSFT)) {   // MOD_LSFT bit matches L+R shift
        uint16_t next = next_keycode;
        if (IS_QK_MOD_TAP(next))   next = QK_MOD_TAP_GET_TAP_KEYCODE(next);
        if (IS_QK_LAYER_TAP(next)) next = QK_LAYER_TAP_GET_TAP_KEYCODE(next);

        const bool wordy = (next >= KC_A && next <= KC_Z) ||
                           next == KC_SPACE || next == KC_DOT || next == KC_COMMA;
        if (!wordy) {
            return 0;   // disable streak for this chord -> opposite-hands hold wins
        }
    }
    return 100;   // letter-to-letter: keep the 100 ms streak protection
}

// Can customize the hold timing
// 500-5000ms suggested
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  return 250;
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
        // commented out since I changed ESC to be macro layer instead of left control
        // if ((other_keycode == KC_F) || (other_keycode == KC_V) || (other_keycode == KC_C) || (other_keycode == KC_X) || (ther_keycode == KC_B)) { return true; }

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
