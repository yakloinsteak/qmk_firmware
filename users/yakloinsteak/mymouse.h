#pragma once

#include <stdint.h>

// Reusable pointer warp. A HID mouse is relative-only, so warp_mouse_pct()
// slams the cursor into the top-left corner of the whole virtual desktop
// (clamps at 0,0) then walks it to a target computed as a percentage of the
// *active monitor layout's* main screen. Because the OS applies pointer
// acceleration to each report, this lands near the target, not exactly on it;
// lower YL_WARP_STEP for more accuracy at the cost of more reports (slower).
// Small step: macOS applies pointer acceleration per report, and at ~1 report/ms
// a large step lands deep in the accelerated region and massively overshoots.
// A small, constant-magnitude step keeps every report near the low (~1:1) end of
// the curve so the walk tracks the requested pixels. Lower = more accurate but
// more reports (slower). See warp calibration notes in mymouse.c.
#ifndef YL_WARP_STEP
#    define YL_WARP_STEP 4 // px moved per report while warping (1..127)
#endif

// Pointer-acceleration compensation. macOS scales our relative reports by a
// factor that is ~constant for a fixed step, so the walk lands short (or long).
// Commanded distance is multiplied by NUM/DEN to compensate. Calibrate: warp to
// center; if it lands at F% instead of 50%, multiply NUM/DEN by 50/F. Because
// the walk moves one axis at a time (see mouse_walk), a single gain fixes both.
#ifndef YL_WARP_GAIN_NUM
#    define YL_WARP_GAIN_NUM 1
#endif
#ifndef YL_WARP_GAIN_DEN
#    define YL_WARP_GAIN_DEN 1
#endif

// Max monitors any one layout describes (sizes the LAYOUTS mon[] arrays).
#define YL_MAX_MON 3

// Selectable monitor layouts. Each has its own screen geometry (see the table
// in mymouse.c). The live layout is persisted to EEPROM. Bind a key to each of
// the YL_MON* keycodes to switch.
typedef enum {
    MON_LAPTOP = 0,
    MON_HOME,
    MON_OFFICE,
    MON_COUNT,
} mon_layout_t;

// Which physical screen a warp targets, left-to-right.
enum yl_screen { YL_SCREEN_LEFT = 0, YL_SCREEN_CENTER, YL_SCREEN_RIGHT };

// Convention for all warps: +x = right, +y = DOWN (negative to go left/up).

// Absolute warp to (px%, py%) of the active layout's main monitor.
// px/py are integer percentages 0..100 (clamped). Pins to the corner first, so
// this is the reliable choice for hitting a fixed point.
void warp_mouse_pct(uint8_t px, uint8_t py);

// Absolute warp to pixel (x, y) within the active layout's main monitor
// (0,0 = that monitor's top-left). Also pins to the corner first.
void warp_mouse_px(int16_t x, int16_t y);

// Relative nudge from the current cursor position (no corner pin). Prefer a
// SHORT nudge after an absolute warp — long relative moves drift.
void warp_mouse_move_px(int16_t dx, int16_t dy);         // in pixels
void warp_mouse_pct_relative(int8_t dx_pct, int8_t dy_pct); // in % of main monitor

// Warp to the center of the layout's left / center / right monitor (clamps to
// the monitors present). Pass a YL_SCREEN_* value.
void warp_mouse_to_screen(uint8_t which);

// Convenience: warp to the center of the active layout's primary monitor.
void warp_mouse_to_center(void);

// Select / query the live monitor layout. mon_layout_set() persists across
// power cycles; mon_layout_get() lazy-loads from EEPROM on first use.
void    mon_layout_set(uint8_t idx);
uint8_t mon_layout_get(void);

// Human-readable name for a layout (for the OLED). Returns "?" if out of range.
const char *mon_layout_name(uint8_t idx);
