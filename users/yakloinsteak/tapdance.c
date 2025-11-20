#include "tapdance.h"
#include QMK_KEYBOARD_H

void double_left(tap_dance_state_t *state, void *user_data, uint16_t code) {
    if (state->count == 1) {
      tap_code16(code);
      reset_tap_dance(state);
    } else if (state->count == 2) {
      tap_code16(code);
      tap_code16(code);
      tap_code16(KC_LEFT);
      reset_tap_dance(state);
    }
}

void magic_quote(tap_dance_state_t *state, void *user_data) {
    double_left(state, user_data, KC_QUOTE);
}

void magic_grave(tap_dance_state_t *state, void *user_data) {
    double_left(state, user_data, KC_GRAVE);
}

void cls_helper(tap_dance_state_t *state, void *user_data, uint16_t code) {
    if (state->count == 1) {
      tap_code16(code);
      reset_tap_dance(state);
    } else if (state->count == 2) {
      SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LALT)"l"SS_UP(X_LCTL)SS_UP(X_LALT));
      tap_code16(code);
      reset_tap_dance(state);
    }
}

void cls_enter(tap_dance_state_t *state, void *user_data) {
    cls_helper(state, user_data, KC_ENTER);
}

/* void underscore_u(tap_dance_state_t *state, void *user_data) { */
/*     if (state->count == 1) { */
/*       tap_code16(KC_U); */
/*       reset_tap_dance(state); */
/*     } else if (state->count == 2) { */
/*       tap_code16(KC_UNDERSCORE); */
/*       reset_tap_dance(state); */
/*     } else if (state->count == 3) { */
/*       tap_code16(KC_MINUS); */
/*       reset_tap_dance(state); */
/*     } */
/* } */


// https://docs.qmk.fm/features/tap_dance#how-to-use
tap_dance_action_t tap_dance_actions[] = {
    [TD_QUOT] = ACTION_TAP_DANCE_FN(magic_quote), // Tap once for ', twice for two quotes and a backspace
    [TD_GRAV] = ACTION_TAP_DANCE_FN(magic_grave), // similar ^
    [TD_ENTER] = ACTION_TAP_DANCE_FN(cls_enter),
    /* [TD_U] = ACTION_TAP_DANCE_FN(underscore_u), */
};
