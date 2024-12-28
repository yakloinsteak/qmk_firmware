#pragma once

/*
 * Tapping behavior
 */

// If you're having trouble hitting the combo keys at the same time, you can
// increase this value
// #define COMBO_TERM 50

// #define QUICK_TAP_TERM 150

// https://docs.qmk.fm/tap_hold
// If you're getting the mod of the mod-tap behavior accidentially: increase
// adjust on the fly for debug/testing on layer fn2 up/down/x
//#undef TAPPING_TERM
#define TAPPING_TERM 205
#define TAPPING_TERM_PER_KEY

// tap-dance I think
#define TAPPING_TOGGLE 2

// https://docs.qmk.fm/tap_hold#permissive-hold
// hitting another key before tap timeout will do the hold action, but you
// cannot release the first key within tapping term.
#define PERMISSIVE_HOLD

// Similar, but if you release the first key and still want the hold action:
// These can be fine-tuned per key if needed. See https://docs.qmk.fm/tap_hold#hold-on-other-key-press
// Might not work with achordion if you exclude the _per_key def as well?
#define HOLD_ON_OTHER_KEY_PRESS
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Try with and without. For fast typists like me, it may help. Mod-taps
// bracketed by regular keys help not make the middle one a mod.
// might prevent the home row mod of D from activating I think.
#define ACHORDION_STREAK

/*
 *
 * Mouse
 *
 */

// Allow kinetic speed with accelertion, but also allow three explicity speeds with ACL0/1/2
#define MK_COMBINED

// do we need this with the previous one?
#define MK_KINETIC_SPEED

#define MOUSEKEY_DELAY 5 //Delay between pressing a movement key and cursor movement
#define MOUSEKEY_INTERVAL 10 //Time between cursor movements in milliseconds
#define MOUSEKEY_MOVE_DELTA 16 //Step size for accelerating from initial to base speed
#define MOUSEKEY_INITIAL_SPEED 100 //Initial speed of the cursor in pixel per second
#define MOUSEKEY_BASE_SPEED 1000 // Maximum cursor speed at which acceleration stops
#define MOUSEKEY_DECELERATED_SPEED 500 // Decelerated cursor speed
#define MOUSEKEY_ACCELERATED_SPEED 2000 // Accelerated cursor speed
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16 //Initial number of movements of the mouse wheel
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32 //Maximum number of movements at which acceleration stops
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
