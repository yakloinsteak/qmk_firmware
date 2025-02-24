#include "action_layer.h"
#include <stdio.h>

#define L_BASE 0
#define L_TAB_HOLD_LAYER (1 << 1)
#define L_LOWER (1 << 2)
#define L_UPPER (1 << 3)
#define L_ADJUST (1 << 4)
#define L_ADJUST_TRI (L_ADJUST | L_UPPER | L_LOWER)
#define L_MACROS (1 << 5)
#define L_UTIL (1 << 6)
#define L_UTIL_TRI (L_UTIL | L_MACROS | L_LOWER)

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
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Mouse");
    break;
  case L_UPPER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Numbers");
    break;
  case L_ADJUST_TRI:
  case L_ADJUST:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Pairs");
    break;
  case L_MACROS:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Macros");
    break;
  case L_UTIL_TRI:
  case L_UTIL:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Utility");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%u", layer_state);
  }

  return layer_state_str;
}
