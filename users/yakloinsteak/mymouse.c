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

// Pin the cursor to the top-left of the virtual desktop, then walk it to the
// absolute pixel (tx, ty). pin_w/pin_h must be >= the full desktop size so the
// corner is reached from anywhere; overshoot is clamped by the OS at 0,0.
static void warp_to_pixel(int32_t pin_w, int32_t pin_h, int32_t tx, int32_t ty) {
    report_mouse_t report = {0};

    // 1. Pin to top-left corner.
    for (int32_t x = pin_w, y = pin_h; x > 0 || y > 0;) {
        report.x = (x > 127) ? -127 : (mouse_xy_report_t)-x;
        report.y = (y > 127) ? -127 : (mouse_xy_report_t)-y;
        host_mouse_send(&report);
        x += report.x; // report.x is <= 0
        y += report.y;
        wait_ms(1);
    }

    // 2. Walk to (tx, ty) in YL_WARP_STEP-sized reports.
    for (int32_t x = tx, y = ty; x > 0 || y > 0;) {
        report.x = (x > YL_WARP_STEP) ? YL_WARP_STEP : (mouse_xy_report_t)x;
        report.y = (y > YL_WARP_STEP) ? YL_WARP_STEP : (mouse_xy_report_t)y;
        host_mouse_send(&report);
        x -= report.x;
        y -= report.y;
        wait_ms(1);
    }

    // 3. Zero report so no residual motion sticks.
    report.x = 0;
    report.y = 0;
    host_mouse_send(&report);
}

void warp_mouse_pct(uint8_t px, uint8_t py) {
    if (px > 100) px = 100;
    if (py > 100) py = 100;

    const uint8_t idx = mon_layout_get();
    int32_t       tx  = (int32_t)LAYOUTS[idx].ox + (int32_t)px * LAYOUTS[idx].w / 100;
    int32_t       ty  = (int32_t)LAYOUTS[idx].oy + (int32_t)py * LAYOUTS[idx].h / 100;

    warp_to_pixel(LAYOUTS[idx].dw, LAYOUTS[idx].dh, tx, ty);
}

void warp_mouse_to_center(void) {
    warp_mouse_pct(50, 50);
}
