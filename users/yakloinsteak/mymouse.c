#include QMK_KEYBOARD_H
#include "mymouse.h"

// Monitor layouts. A relative HID mouse can only pin to (0,0) of the *whole*
// virtual desktop, so each layout lists its monitors left-to-right in *logical
// points* (macOS CGDisplayBounds units — HiDPI-aware, NOT physical pixels),
// names the primary (macOS "main") display, and gives the desktop pin span
// (dw,dh — must cover the whole union so a corner-pin always lands at 0,0).
// Get the numbers on the host with the CGDisplayBounds swift dump (see runme).
typedef struct {
    int16_t x, y, w, h; // rect in global logical points (x/y may be off-origin)
} yl_mon_t;

static const struct {
    const char *name;
    uint8_t     count;          // monitors in use (<= YL_MAX_MON)
    yl_mon_t    mon[YL_MAX_MON]; // ordered left-to-right by x
    uint8_t     primary;        // index of the macOS main display (dialogs center here)
    uint16_t    dw, dh;         // pin span; must cover the whole desktop union
} LAYOUTS[MON_COUNT] = {
    [MON_LAPTOP] = {"Laptop", 1, {{0, 0, 1512, 982}}, 0, 1512, 982}, // 14" MBP, logical pts
    // Home (measured, logical pts): external @-1920,-368 1920x1200 is the primary
    // work monitor, physically LEFT; laptop @0,0 1512x982 is the macOS main display,
    // physically RIGHT. Ordered left-to-right, so mon[0]=external, mon[1]=laptop.
    [MON_HOME]   = {"Home", 2, {{-1920, -368, 1920, 1200}, {0, 0, 1512, 982}}, 1, 3500, 1400},
    // Office (measured, logical pts): left=main @0,0 1800x1169 | center/VM @1800,89 1920x1080 | right @3720,-31 1600x1200
    [MON_OFFICE] = {"Office", 3, {{0, 0, 1800, 1169}, {1800, 89, 1920, 1080}, {3720, -31, 1600, 1200}}, 0, 5400, 1220},
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
// Each axis is walked separately (never diagonally) so every report moves at the
// same per-report speed and thus the same OS acceleration gain — a diagonal
// segment would scale x and y differently. Commanded distance is pre-scaled by
// YL_WARP_GAIN_* to compensate for that (roughly constant) gain.
//
// Y is walked BEFORE X on purpose. We start pinned at the desktop's top-left
// corner (top of the primary monitor). Side monitors may not extend all the way
// up to y=0 (e.g. one starting at y=89), so walking X first along y=0 runs into
// the void past the primary monitor's right edge and the cursor clamps there.
// Descending to the target y first (inside the full-height primary monitor) and
// then crossing X at that row — where the monitors overlap vertically — keeps
// the path on real screen the whole way.
static void mouse_walk(int32_t dx, int32_t dy) {
    dx = dx * YL_WARP_GAIN_NUM / YL_WARP_GAIN_DEN;
    dy = dy * YL_WARP_GAIN_NUM / YL_WARP_GAIN_DEN;
    int32_t sy = (dy < 0) ? -1 : 1, ay = (dy < 0) ? -dy : dy;
    while (ay > 0) {
        int32_t step = (ay > YL_WARP_STEP) ? YL_WARP_STEP : ay;
        mouse_report(0, (mouse_xy_report_t)(sy * step));
        ay -= step;
    }
    int32_t sx = (dx < 0) ? -1 : 1, ax = (dx < 0) ? -dx : dx;
    while (ax > 0) {
        int32_t step = (ax > YL_WARP_STEP) ? YL_WARP_STEP : ax;
        mouse_report((mouse_xy_report_t)(sx * step), 0);
        ax -= step;
    }
    mouse_report(0, 0); // stop
}

// Pin the cursor to the top-left corner of the LEFTMOST monitor (mon[0]) using
// big 127-px jumps that overshoot and clamp at each edge. One axis at a time:
//
//   LEFT first, at the current row — right after a warp the cursor sits in the
//   monitors' shared vertical band, so travelling left crosses every monitor
//   continuously to the leftmost one's left edge; then UP that column to its top.
//
// Lands at (mon[0].x, mon[0].y), which may be NEGATIVE when a monitor sits left
// of / above the macOS main display (e.g. home: external at -1920,-368).
// warp_abs offsets targets by that corner. A diagonal pin can wedge at a seam
// where monitors don't share a top edge; a down-first pin can't reach a monitor
// that lives above the bottom rail. pin_w/pin_h must cover the whole union.
//
// Caveat: the LEFT pass assumes the current y is within all monitors' shared
// vertical band (true post-warp / cursor mid-screen). A cursor parked in a
// region only one monitor reaches could clamp early.
static void mouse_pin_topleft(int32_t pin_w, int32_t pin_h) {
    for (int32_t x = pin_w; x > 0;) { // LEFT to the leftmost monitor's edge
        mouse_xy_report_t dx = (x > 127) ? -127 : (mouse_xy_report_t)-x;
        mouse_report(dx, 0);
        x += dx; // dx <= 0
    }
    for (int32_t y = pin_h; y > 0;) { // UP that column to the top
        mouse_xy_report_t dy = (y > 127) ? -127 : (mouse_xy_report_t)-y;
        mouse_report(0, dy);
        y += dy; // dy <= 0
    }
}

// Active layout's primary (macOS main) monitor.
static const yl_mon_t *primary_mon(void) {
    const uint8_t idx = mon_layout_get();
    return &LAYOUTS[idx].mon[LAYOUTS[idx].primary];
}

// Pin to the corner, then walk to a global desktop point (logical points). The
// pin lands at the leftmost monitor's top-left = (mon[0].x, mon[0].y), which may
// be negative, so the walk delta is measured from that corner (both parts >= 0).
static void warp_abs(int32_t gx, int32_t gy) {
    const uint8_t idx = mon_layout_get();
    mouse_pin_topleft(LAYOUTS[idx].dw, LAYOUTS[idx].dh);
    const yl_mon_t *tl = &LAYOUTS[idx].mon[0]; // leftmost monitor = pin landing corner
    mouse_walk(gx - (int32_t)tl->x, gy - (int32_t)tl->y);
}

// Absolute warp to pixel (x, y) within the active layout's primary monitor
// (0,0 = top-left of that monitor). Pins to the desktop corner first.
void warp_mouse_px(int16_t x, int16_t y) {
    const yl_mon_t *p = primary_mon();
    warp_abs((int32_t)p->x + x, (int32_t)p->y + y);
}

void warp_mouse_pct(uint8_t px, uint8_t py) {
    if (px > 100) px = 100;
    if (py > 100) py = 100;
    const yl_mon_t *p = primary_mon();
    warp_mouse_px((int16_t)((int32_t)px * p->w / 100), //
                  (int16_t)((int32_t)py * p->h / 100));
}

// Warp to the center of the layout's left / center / right monitor.
// which = YL_SCREEN_LEFT / _CENTER / _RIGHT; clamps to the monitors present
// (a 1-monitor layout sends all three to that monitor).
void warp_mouse_to_screen(uint8_t which) {
    const uint8_t idx = mon_layout_get();
    const uint8_t n   = LAYOUTS[idx].count;
    const uint8_t m   = (which == YL_SCREEN_LEFT)  ? 0
                      : (which == YL_SCREEN_RIGHT) ? (uint8_t)(n - 1)
                                                   : (uint8_t)((n - 1) / 2);
    const yl_mon_t *s = &LAYOUTS[idx].mon[m];
    warp_abs((int32_t)s->x + s->w / 2, (int32_t)s->y + s->h / 2);
}

// Relative nudge from the current position, in pixels. +x right, +y down.
void warp_mouse_move_px(int16_t dx, int16_t dy) {
    mouse_walk(dx, dy);
}

// Relative nudge as a percentage of the active layout's primary monitor.
// Signed: +x right / +y down, negative for left / up.
void warp_mouse_pct_relative(int8_t dx_pct, int8_t dy_pct) {
    const yl_mon_t *p = primary_mon();
    mouse_walk((int32_t)dx_pct * p->w / 100, //
               (int32_t)dy_pct * p->h / 100);
}

void warp_mouse_to_center(void) {
    warp_mouse_pct(50, 50);
}

// Bounding box of the union of all monitors in the active layout, in global
// logical points. Unlike warp_mouse_pct (which targets the primary monitor),
// this spans the whole virtual desktop so a fraction maps across every screen.
static void desktop_bbox(int32_t *ox, int32_t *oy, int32_t *ow, int32_t *oh) {
    const uint8_t idx = mon_layout_get();
    int32_t minx = INT32_MAX, miny = INT32_MAX, maxx = INT32_MIN, maxy = INT32_MIN;
    for (uint8_t i = 0; i < LAYOUTS[idx].count; i++) {
        const yl_mon_t *m = &LAYOUTS[idx].mon[i];
        if (m->x < minx) minx = m->x;
        if (m->y < miny) miny = m->y;
        if (m->x + m->w > maxx) maxx = m->x + m->w;
        if (m->y + m->h > maxy) maxy = m->y + m->h;
    }
    *ox = minx; *oy = miny; *ow = maxx - minx; *oh = maxy - miny;
}

// Warp to (fx, fy) as a 0..255 fraction of the whole virtual-desktop union.
// Pins to the corner first (via warp_abs), so it hits a fixed point.
void warp_mouse_desktop_frac(uint8_t fx, uint8_t fy) {
    int32_t ox, oy, ow, oh;
    desktop_bbox(&ox, &oy, &ow, &oh);
    warp_abs(ox + (int32_t)fx * ow / 255, oy + (int32_t)fy * oh / 255);
}

// Packed warp target for the WARP-layer key at matrix (row, col). Weak default
// = desktop center; each board's keymap overrides it with its own LAYOUT table.
__attribute__((weak)) uint16_t yl_warp_target(uint8_t row, uint8_t col) {
    return 0x8080;
}
