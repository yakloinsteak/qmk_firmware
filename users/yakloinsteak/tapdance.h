#pragma once

#include QMK_KEYBOARD_H

enum {
  TD_QUOT,
  TD_GRAV,
};

void magic_quote(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[2];
