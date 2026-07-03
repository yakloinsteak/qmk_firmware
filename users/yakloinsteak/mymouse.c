#include QMK_KEYBOARD_H
#include "mymouse.h"

// YL_CTR: move the mouse pointer to (roughly) the center of the screen.
// A HID mouse is relative-only, so first pin the cursor to the top-left corner
// (repeated max moves clamp at 0,0 regardless of where it started), then step
// it back to the center. The OS applies pointer acceleration to each report,
// so this lands near the center, not exactly on it. Tune YL_CENTER_X/Y (half
// screen resolution) and YL_CENTER_STEP in mymouse.h
void warp_mouse_to_center(void) {
    report_mouse_t report = {0};

    // 1. Pin to top-left: move up-left by a full screen in each axis so the
    //    cursor reaches 0,0 from anywhere. Overshoot is clamped by the OS.
    for (int16_t x = 2 * YL_CENTER_X, y = 2 * YL_CENTER_Y; x > 0 || y > 0;) {
        report.x = (x > 127) ? -127 : (mouse_xy_report_t)-x;
        report.y = (y > 127) ? -127 : (mouse_xy_report_t)-y;
        host_mouse_send(&report);
        x += report.x; // report.x is <= 0
        y += report.y;
        wait_ms(1);
    }

    // 2. Walk to the center in YL_CENTER_STEP-sized reports.
    for (int16_t x = YL_CENTER_X, y = YL_CENTER_Y; x > 0 || y > 0;) {
        report.x = (x > YL_CENTER_STEP) ? YL_CENTER_STEP : (mouse_xy_report_t)x;
        report.y = (y > YL_CENTER_STEP) ? YL_CENTER_STEP : (mouse_xy_report_t)y;
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
