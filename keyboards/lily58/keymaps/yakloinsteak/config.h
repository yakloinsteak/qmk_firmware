#pragma once

#define TRI_LAYER_LOWER_LAYER LOWER
#define TRI_LAYER_UPPER_LAYER UPPER
#define TRI_LAYER_ADJUST_LAYER ADJUST

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 210
#define TAPPING_TOGGLE 2

// Maybe want permissive_hold instead?
#define HOLD_ON_OTHER_KEY_PRESS

#define HRM HRM_ACHORDION

// Try with and without. For fast typists like me, it may help. Mod-taps
// bracketed by regular keys help not make the middle one a mod.
// pody would prevent the home row mod of D from activating I think.
#define ACHORDION_STREAK

// If you're having trouble hitting the combo keys at the same time, you can
// increase this value
// #define COMBO_TERM 50

// #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Allow kinetic speed with accelertion, but also allow three explicity speeds with ACL0/1/2
#define MK_COMBINED

#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY 5 //Delay between pressing a movement key and cursor movement
#define MOUSEKEY_INTERVAL 10 //Time between cursor movements in milliseconds
#define MOUSEKEY_MOVE_DELTA 16 //Step size for accelerating from initial to base speed
#define MOUSEKEY_INITIAL_SPEED 100 //Initial speed of the cursor in pixel per second
#define MOUSEKEY_BASE_SPEED 5000 //Maximum cursor speed at which acceleration stops
#define MOUSEKEY_DECELERATED_SPEED 400 // Decelerated cursor speed
#define MOUSEKEY_ACCELERATED_SPEED 3000 // Accelerated cursor speed
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16 //Initial number of movements of the mouse wheel
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32 //Maximum number of movements at which acceleration stops
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48

#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_LED_COUNT 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

// Underglow
/*
#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_LED_COUNT 14    // Number of LEDs
#define RGBLIGHT_SLEEP
*/
