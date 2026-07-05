#pragma once

#include <stdint.h>

// Reusable pointer warp. A HID mouse is relative-only, so warp_mouse_pct()
// slams the cursor into the top-left corner of the whole virtual desktop
// (clamps at 0,0) then walks it to a target computed as a percentage of the
// *active monitor layout's* main screen. Because the OS applies pointer
// acceleration to each report, this lands near the target, not exactly on it;
// lower YL_WARP_STEP for more accuracy at the cost of more reports (slower).
#ifndef YL_WARP_STEP
#    define YL_WARP_STEP 70 // px moved per report while warping (1..127)
#endif

// Selectable monitor layouts. Each has its own screen geometry (see the table
// in mymouse.c). The live layout is persisted to EEPROM. Bind a key to each of
// the YL_MON* keycodes to switch.
typedef enum {
    MON_LAPTOP = 0,
    MON_HOME,
    MON_OFFICE,
    MON_COUNT,
} mon_layout_t;

// Move the pointer to (px%, py%) of the active layout's main monitor.
// px/py are integer percentages 0..100 (clamped).
void warp_mouse_pct(uint8_t px, uint8_t py);

// Convenience: warp to the center of the active layout's main monitor.
void warp_mouse_to_center(void);

// Select / query the live monitor layout. mon_layout_set() persists across
// power cycles; mon_layout_get() lazy-loads from EEPROM on first use.
void    mon_layout_set(uint8_t idx);
uint8_t mon_layout_get(void);

// Human-readable name for a layout (for the OLED). Returns "?" if out of range.
const char *mon_layout_name(uint8_t idx);
