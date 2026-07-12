#include QMK_KEYBOARD_H

#include "mylayers.h"

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, LTHUMB_2R, RTHUMB_2L, THUMBS_INWARD);
  state = update_tri_layer_state(state, LTHUMB_2R, MACROS, UTIL);
/* #ifdef CONSOLE_ENABLE */
/*   dprintf("layer: %i\n", get_highest_layer(state)); */
/* #endif */
  return state;
}
