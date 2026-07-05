#include QMK_KEYBOARD_H
#include "mymouse.h"

// Monitor layouts. A relative HID mouse can only pin to (0,0) of the *whole*
// virtual desktop, so each layout stores both the main monitor's rect (origin
// ox,oy + size w,h — what percentages are measured against) and the full
// desktop size (dw,dh — how far to travel to reach the top-left corner).
// Seeded from ~/.config/i3/xrandr; edit to match your actual setups.
static const struct {
    const char *name;
    uint16_t    ox, oy; // main monitor origin within the virtual desktop
    uint16_t    w, h;   // main monitor size
    uint16_t    dw, dh; // full virtual desktop size (for corner-pinning)
} LAYOUTS[MON_COUNT] = {
    [MON_LAPTOP] = {"Laptop", 0, 0, 1920, 1080, 1920, 1080},
    [MON_HOME]   = {"Home", 0, 0, 1920, 1200, 3840, 1253},   // HDMI-0 primary @0,0 + laptop to the right
    [MON_OFFICE] = {"Office", 1920, 0, 3840, 2160, 5760, 2160}, // HDMI-0 4K @1920,0 + laptop @0,730
};

// ---- persistence -----------------------------------------------------------

// Claims the userspace EEPROM block (the userspace has no other eeconfig use).
typedef union {
    uint32_t raw;
    struct {
        uint8_t monitor_layout;
    };
} yl_user_config_t;

static uint8_t s_layout = 0xFF; // 0xFF = not yet loaded from EEPROM

uint8_t mon_layout_get(void) {
    if (s_layout == 0xFF) {
        yl_user_config_t c = {.raw = eeconfig_read_user()};
        s_layout           = (c.monitor_layout < MON_COUNT) ? c.monitor_layout : MON_LAPTOP;
    }
    return s_layout;
}

void mon_layout_set(uint8_t idx) {
    if (idx >= MON_COUNT) return;
    s_layout           = idx;
    yl_user_config_t c = {.raw = eeconfig_read_user()};
    c.monitor_layout   = idx;
    eeconfig_update_user(c.raw);
}

const char *mon_layout_name(uint8_t idx) {
    return (idx < MON_COUNT) ? LAYOUTS[idx].name : "?";
}

// Seed the default layout on first flash / EEPROM reset (EE_CLR). Safe to
// define here: no keymap defines eeconfig_init_user.
void eeconfig_init_user(void) {
    eeconfig_update_user(0); // monitor_layout = MON_LAPTOP
}

// ---- warping ---------------------------------------------------------------
//
// Coordinate convention (matches warp_mouse_pct): +x = right, +y = DOWN.
// To go up/left, pass a negative delta.
//
// Accuracy note: firmware cannot read the OS cursor position, so a purely
// *relative* move has no known origin and errors compound. For hitting a fixed
// point, prefer an *absolute* warp (warp_mouse_px / warp_mouse_pct) which first
// pins to the top-left corner to re-establish a known origin. All moves are
// walked in small YL_WARP_STEP increments so OS pointer acceleration (which
// scales with per-report speed) distorts them as little as possible.

// Send one relative report, clamped to the int8 mouse range, then settle.
static void mouse_report(mouse_xy_report_t dx, mouse_xy_report_t dy) {
    report_mouse_t report = {0};
    report.x              = dx;
    report.y              = dy;
    host_mouse_send(&report);
    wait_ms(1);
}

// Walk a relative delta (dx, dy; may be negative) in YL_WARP_STEP-sized reports.
static void mouse_walk(int32_t dx, int32_t dy) {
    int32_t sx = (dx < 0) ? -1 : 1, ax = (dx < 0) ? -dx : dx;
    int32_t sy = (dy < 0) ? -1 : 1, ay = (dy < 0) ? -dy : dy;
    while (ax > 0 || ay > 0) {
        int32_t stepx = (ax > YL_WARP_STEP) ? YL_WARP_STEP : ax;
        int32_t stepy = (ay > YL_WARP_STEP) ? YL_WARP_STEP : ay;
        mouse_report((mouse_xy_report_t)(sx * stepx), (mouse_xy_report_t)(sy * stepy));
        ax -= stepx;
        ay -= stepy;
    }
    mouse_report(0, 0); // stop
}

// Pin the cursor to (0,0) of the virtual desktop using big -127 jumps.
// pin_w/pin_h must be >= the full desktop size; overshoot is clamped at 0,0.
static void mouse_pin_topleft(int32_t pin_w, int32_t pin_h) {
    for (int32_t x = pin_w, y = pin_h; x > 0 || y > 0;) {
        mouse_xy_report_t dx = (x > 127) ? -127 : (mouse_xy_report_t)-x;
        mouse_xy_report_t dy = (y > 127) ? -127 : (mouse_xy_report_t)-y;
        mouse_report(dx, dy);
        x += dx; // dx is <= 0
        y += dy;
    }
}

// Absolute warp to pixel (x, y) within the active layout's main monitor
// (0,0 = top-left of that monitor). Pins to the desktop corner first.
void warp_mouse_px(int16_t x, int16_t y) {
    const uint8_t idx = mon_layout_get();
    mouse_pin_topleft(LAYOUTS[idx].dw, LAYOUTS[idx].dh);
    mouse_walk((int32_t)LAYOUTS[idx].ox + x, (int32_t)LAYOUTS[idx].oy + y);
}

void warp_mouse_pct(uint8_t px, uint8_t py) {
    if (px > 100) px = 100;
    if (py > 100) py = 100;
    const uint8_t idx = mon_layout_get();
    warp_mouse_px((int16_t)((int32_t)px * LAYOUTS[idx].w / 100), //
                  (int16_t)((int32_t)py * LAYOUTS[idx].h / 100));
}

// Relative nudge from the current position, in pixels. +x right, +y down.
void warp_mouse_move_px(int16_t dx, int16_t dy) {
    mouse_walk(dx, dy);
}

// Relative nudge as a percentage of the active layout's main monitor.
// Signed: +x right / +y down, negative for left / up.
void warp_mouse_pct_relative(int8_t dx_pct, int8_t dy_pct) {
    const uint8_t idx = mon_layout_get();
    mouse_walk((int32_t)dx_pct * LAYOUTS[idx].w / 100, //
               (int32_t)dy_pct * LAYOUTS[idx].h / 100);
}

void warp_mouse_to_center(void) {
    warp_mouse_pct(50, 50);
}
