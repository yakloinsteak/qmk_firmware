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
 */
__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) { return false; }

    /* if (IS_LAYER_ON(TMUX) && record->event.pressed) { */
    /*     tap_code16(C(KC_A));  // Tap Ctrl+A. */
    /* } */

#   ifdef OLED_ENABLE
    if (record->event.pressed) {
      set_keylog(keycode, record);
      // set_timelog();
    }
#   endif

    switch (keycode) {
    case SNIPPETS:
        if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"Z"SS_DELAY(100)"snippets"SS_TAP(X_ENT)); }
        break;
    case YL_WRIT:
        if (record->event.pressed) { SEND_STRING(SS_TAP(X_ESC)":w"SS_TAP(X_ENT)); }
        break;
    case SWITCH_WINDOW:
        if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"s"); }
        break;
    /*
     * TODO:
     *   <esc>:q<enter>
     *
     * */
    case MAGIC_QUOTE:
        if (record->event.pressed) { SEND_STRING("''\b"); }
        break;
    case UPDIR:
        if (record->event.pressed) { SEND_STRING("../"); }
        return false; // skip any further pipeline processing which wouldn't be happening for custom keys anyway
        /* break; */
    case DBLCLK:  // Double click the left mouse button.
        if (record->event.pressed) { SEND_STRING(SS_TAP(X_BTN1) SS_DELAY(50) SS_TAP(X_BTN1)); }
        return false;

#   ifdef DIGITIZER_ENABLE
    case YL_CTR:
        if (record->event.pressed) {
            digitizer_in_range_on();
            digitizer_set_position(0.5, 0.5);
            digitizer_flush();
        }
        return true;
#   endif

    }

  return true;
}
