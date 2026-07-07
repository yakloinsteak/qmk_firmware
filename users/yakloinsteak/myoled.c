#include QMK_KEYBOARD_H
#include "mylayers.h"
#include "mymouse.h"

// Shared OLED for all yakloinsteak boards with a display. The master half shows
// the current layer + active modifiers (and the monitor layout on the Mouse
// layer); the slave half (and the base layer) shows the board logo. The logo
// bytes are glyph indices into the per-board OLED font (set via OLED_FONT_H at
// the keyboard level), so the same array renders each board's own logo.

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};

    oled_write_P(logo, false);
}

// Print the active modifiers and Caps Word as a compact status line.
static void render_mods(void) {
    uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods();
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("S") : PSTR("-"), false);
    oled_write_P((mods & MOD_MASK_CTRL)  ? PSTR("C") : PSTR("-"), false);
    oled_write_P((mods & MOD_MASK_ALT)   ? PSTR("A") : PSTR("-"), false);
    oled_write_P((mods & MOD_MASK_GUI)   ? PSTR("G") : PSTR("-"), false);
    oled_write_P(is_caps_word_on() ? PSTR(" CAPS\n") : PSTR("\n"), false);
}

static void render_status(void) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == BASE) {
        render_logo();  // logo fills the whole display on the base layer
        return;
    }
    oled_clear();  // wipe the logo/previous layer text before drawing this layer
    switch (layer) {
        case TAB_HOLD_LAYER:
            oled_write_P(PSTR("Layer: Nav\n"), false);
            break;
        case LTHUMB_2R:
            oled_write_P(PSTR("Layer: Mouse\n"), false);
            oled_write_P(PSTR("Mon: "), false);
            oled_write(mon_layout_name(mon_layout_get()), false);
            oled_write_P(PSTR("\n"), false);
            break;
        case RTHUMB_2L:
            oled_write_P(PSTR("Layer: Num/Sym\n"), false);
            break;
        case THUMBS_INWARD:
            oled_write_P(PSTR("Layer: Fn\n"), false);
            break;
        case MACROS:
            oled_write_P(PSTR("Layer: Macros\n"), false);
            break;
        case UTIL:
            oled_write_P(PSTR("Layer: Util\n"), false);
            break;
        case SYMBOLS:
            oled_write_P(PSTR("Layer: Symbols\n"), false);
            break;
        case CRYPT:
            oled_write_P(PSTR("Layer: Crypt\n"), false);
            break;
        default:
            oled_write_P(PSTR("Layer: "), false);
            oled_write(get_u8_str(layer, ' '), false);
            oled_write_P(PSTR("\n"), false);
    }
    render_mods();
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();  // Renders a static logo
    }
    return false;
}

#endif // OLED_ENABLE
