#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"
#include "achordion.h"

void set_keylog(uint16_t keycode, keyrecord_t *record);

/* tap_code(kc) to tap an individual key
   register_code(kc) and unregister_code(kc) to press down and release a key.

   record->event.pressed is true if the event is a press (key down), and false if it is a release (key up).

   record->event.time is a 16-bit timestamp in units of milliseconds of when the event occurred

   record->event.key.row and record->event.key.col are the matrix position of the key, counting from 0.

   If the event comes from a mod-tap (MT) or layer-tap (LT) key, then
   record->tap.count is zero if the key is considered held, otherwise it is
   considered tapped (see also Intercepting Mod-Taps and Achordion).

   get_mods() returns a bitfield of which modifiers are currently active, and
   similarly get_oneshot_mods() for one-shot modifiers (see also Checking
   Modifier State and the next section, Macros that respond to mods).

   Get the layer associated with the key event:
   uint8_t layer = read_source_layers_cache(record->event.key);

   IS_LAYER_ON(layer) returns whether layer is currently on, and

   get_highest_layer(layer_state) returns the highest layer that is currently
   on (see also Working with Layers).

   get_repeat_key_count() indicates whether the key is being invoked through
   Repeat Key or Alternate Repeat Key (see also Repeat Key functions).

   register_code(KC_LCTL); // Change the key to be held here
   unregister_code(KC_LCTL); // Change the key that was held here, too!
 */
__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t tmux_timer;
    static bool tmux_on = false;

    if (!process_achordion(keycode, record)) { return false; }

    if (tmux_on && timer_elapsed(tmux_timer) >= TAPPING_TERM && record->event.pressed) {
        tap_code16(C(KC_A));  // Tap Ctrl+A before subsequent taps.
    }

#   ifdef OLED_ENABLE
    if (record->event.pressed) {
      set_keylog(keycode, record);
      // set_timelog();
    }
#   endif

    switch (keycode) {
    case YL_CTLA:
        if (record->event.pressed) {
            tmux_timer = timer_read();
            tmux_on = true;
        } else {
            if (timer_elapsed(tmux_timer) < TAPPING_TERM) { tap_code16(C(KC_A)); }
            tmux_on = false;
        }
        return false;
    case YL_SNIP:
        if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"Z"SS_DELAY(100)"snippets"SS_TAP(X_ENT)); }
        break;
    case YL_QUIT:
        if (record->event.pressed) { SEND_STRING(SS_TAP(X_ESC)":q"SS_TAP(X_ENT)); }
        break;
    case YL_WRIT:
        if (record->event.pressed) { SEND_STRING(SS_TAP(X_ESC)":w"SS_TAP(X_ENT)); }
        break;
    case YL_FIAP:
        // firefox insecure approve
        if (record->event.pressed) { send_string_with_delay("\t\t\t " SS_DELAY(400) "\t\t\t\t ", 100); }
        break;
    case YL_WSCH:
        if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"s"); }
        break;
    case UPDIR:
        if (record->event.pressed) { SEND_STRING("../"); }
        return false; // skip any further pipeline processing which wouldn't be happening for custom keys anyway
        /* break; */
    case DBLCLK:  // Double click the left mouse button.
        if (record->event.pressed) { SEND_STRING(SS_TAP(X_BTN1) SS_DELAY(50) SS_TAP(X_BTN1)); }
        return false;
    case YL_SLSH:
        if (record->event.pressed) { tap_code16(KC_SLSH); }
        return false;
    case YL_LT:
        if (record->event.pressed) { tap_code16(KC_LT); }
        return false;
    case YL_LBRC:
        if (record->event.pressed) { tap_code16(KC_LBRC); }
        return false;
    case YL_LCBR:
        if (record->event.pressed) { tap_code16(KC_LCBR); }
        return false;
    case YL_RCBR:
        if (record->event.pressed) { tap_code16(KC_RCBR); }
        return false;
    case YL_RBRC:
        if (record->event.pressed) { tap_code16(KC_RBRC); }
        return false;
    case YL_GT:
        if (record->event.pressed) { tap_code16(KC_GT); }
        return false;
    case YL_BSLS:
        if (record->event.pressed) { tap_code16(KC_BSLS); }
        return false;
    case YL_BACK:
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_SHIFT) {
              tap_code16(KC_DEL);
            } else {
              tap_code16(KC_BSPC);
            }
        }
        return false;

#   ifdef DIGITIZER_ENABLE
    case YL_CTR:
        if (record->event.pressed) {
            digitizer_in_range_on();
            digitizer_set_position(0.5, 0.5);
            digitizer_flush();
        }
        return false;
#   endif

    }

  return true;
}
