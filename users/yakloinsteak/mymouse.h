#pragma once

// YL_CTR "warp cursor to screen center". A HID mouse is relative-only, so we
// slam the pointer into the top-left corner (clamps at 0,0) then walk it back
// to the center. Set these to HALF your screen resolution in pixels.
// Because the OS applies pointer acceleration to each report, this lands
// *near* the center, not exactly on it; lower YL_CENTER_STEP for more accuracy
// at the cost of more reports (slower). Must be 1..127.
#ifndef YL_CENTER_X
#    define YL_CENTER_X 960  // half of a 1920-wide screen
#endif
#ifndef YL_CENTER_Y
#    define YL_CENTER_Y 540  // half of a 1080-tall screen
#endif
#ifndef YL_CENTER_STEP
#    define YL_CENTER_STEP 70 // px moved per report while centering (<=127)
#endif

void warp_mouse_to_center(void);
