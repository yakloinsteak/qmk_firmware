#include "action_layer.h"
#include <stdio.h>

#define L_BASE 0
/* #define L_LOWER (1 << 1) */
/* #define L_RAISE (1 << 2) */
/* #define L_ADJUST (1 << 3) */
/* #define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER) */
#define L_TAB_HOLD_LAYER (1 << 1)
#define L_UTIL (1 << 2)
#define L_LOWER (1 << 3)
#define L_UPPER (1 << 4)
#define L_ADJUST (1 << 5)
#define L_U1 (1 << 6)
#define L_U2 (1 << 7)
#define L_U_ADJUST (1 << 8)
#define L_UTIL2 (1 << 9)

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Base");
    break;
  case L_TAB_HOLD_LAYER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Tab Hold");
    break;
  case L_UTIL:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Utility");
    break;
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Mouse");
    break;
  case L_UPPER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Numbers");
    break;
  case L_ADJUST:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Symbols");
    break;
  case L_U1:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Brackets");
    break;
  case L_U2:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Macros");
    break;
  case L_U_ADJUST:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: TMUX");
    break;
  case L_UTIL2:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Unused Util2");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%u", layer_state);
  }

  return layer_state_str;
}
