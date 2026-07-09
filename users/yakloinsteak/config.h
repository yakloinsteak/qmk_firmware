#pragma once

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
//#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

/*
 * Tapping behavior
 */

// If you're having trouble hitting the combo keys at the same time, you can
// increase this value
#define COMBO_TERM 35

// #define QUICK_TAP_TERM 150

// https://docs.qmk.fm/tap_hold
// If you're getting the mod of the mod-tap behavior accidentially: increase
// adjust on the fly for debug/testing on layer fn2 up/down/x
//#undef TAPPING_TERM
// Chordal Hold folds the old achordion_timeout (250 ms) into the tapping term, so
// Getreuer recommends a relatively high base here. Tunable back toward 205 if taps
// feel sluggish. Per-key deltas in tap_hooks.c stay relative to this.
#define TAPPING_TERM 250
#define TAPPING_TERM_PER_KEY

// Hold threshold for the tmux ^a-prefix feature (YL_CTLA in process_record_user.c).
// Kept separate from TAPPING_TERM so tuning the home-row mods doesn't change how long
// you must hold the thumb before it starts prefixing keys. This is the pre-migration
// TAPPING_TERM value, which is the feel this feature was dialed in against.
#define TMUX_PREFIX_HOLD_TERM 205

// tap-dance I think
#define TAPPING_TOGGLE 2

// https://docs.qmk.fm/tap_hold#permissive-hold
// hitting another key before tap timeout will do the hold action, but you
// cannot release the first key within tapping term.
#define PERMISSIVE_HOLD

// Similar, but if you release the first key and still want the hold action:
// These can be fine-tuned per key if needed. See https://docs.qmk.fm/tap_hold#hold-on-other-key-press
// Left off: PERMISSIVE_HOLD is the Chordal Hold pairing we use for opposite-hand holds.
// #define HOLD_ON_OTHER_KEY_PRESS
// #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Home-row-mod tuning, all in QMK core (replaces the vendored Achordion library):
//   CHORDAL_HOLD    - "opposite hands rule": same-hand chords within the tapping
//                     term settle as tap, killing accidental mods on rolls.
//   FLOW_TAP_TERM   - suppresses mods during fast typing (was ACHORDION_STREAK);
//                     100 ms matches the old streak value. Its default only engages
//                     between alpha-area keys, so Shift-rolled-into-symbol still holds.
//   SPECULATIVE_HOLD - applies Shift/Ctrl eagerly on keydown (was achordion_eager_mod;
//                     the default already covers exactly Shift/Ctrl/Shift+Ctrl).
#define CHORDAL_HOLD
#define FLOW_TAP_TERM 100
#define SPECULATIVE_HOLD

/*
 *
 * Mouse
 *
 */

// Allow kinetic speed with accelertion, but also allow three explicity speeds with ACL0/1/2
#define MK_COMBINED

// do we need this with the previous one?
#define MK_KINETIC_SPEED

#define MOUSEKEY_DELAY 5 // Delay between pressing a movement key and cursor movement
#define MOUSEKEY_INTERVAL 10 // Time between cursor movements in milliseconds
#define MOUSEKEY_MOVE_DELTA 16 // Step size for accelerating from initial to base speed
#define MOUSEKEY_MAX_SPEED 5
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_INITIAL_SPEED 100 // Initial speed of the cursor in pixel per second
#define MOUSEKEY_BASE_SPEED 500 // Maximum cursor speed at which acceleration stops
#define MOUSEKEY_DECELERATED_SPEED 100 // Decelerated cursor speed
#define MOUSEKEY_ACCELERATED_SPEED 800 // Accelerated cursor speed

#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16 // Initial number of movements of the mouse wheel
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32 // Maximum number of movements at which acceleration stops
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8

#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS, UNICODE_MODE_LINUX
