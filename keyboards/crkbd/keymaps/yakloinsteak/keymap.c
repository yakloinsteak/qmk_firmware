#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"
#include "combos.h"
#include "achordion.h"
#include "tapdance.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_split_3x6_3(
    YL_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    YL_CRPT,
    YL_ESC,   YL_A,   YL_S,    YL_D,    YL_F,    KC_G,                     KC_H,    YL_J,    YL_K,    YL_L,    YL_SCLN, YL_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, YL_RSFT,
                                   YL_LTH3, KC_ENT, YL_LTH1,        YL_RTH1, YL_SPC, YL_RTH3
),

[TAB_HOLD_LAYER] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_HOME, KC_PGUP, KC_INS,  KC_PSCR, KC_F12,
    _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, KC_DEL,
    _______, _______, _______, _______, _______, _______,                   _______, KC_END,  KC_PGDN, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

/* left thumb layer right of home / mouse */
[LTHUMB_2R] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX, MS_ACL2, XXXXXXX,                   YL_CTR,  MS_BTN1, MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, MS_WHLL, MS_WHLD, MS_WHLR, MS_ACL0, XXXXXXX,                   MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, MS_ACL1, XXXXXXX,                   DBLCLK,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______,                   _______, _______, _______
),

/* Right thumb left of home / homerow mod digits and symbols
 * mirror-pairs below homerow
 * */
[RTHUMB_2L] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_PLUS, _______, _______, _______, _______,
    YL_GRAV, YL_1,    YL_2,    YL_3,    YL_4,    KC_5,                      KC_6,    YL_7,    YL_8,    YL_9,    YL_0,    _______,
    _______, YL_BSLS, YL_LT,   YL_LBRC, YL_LCBR, KC_LPRN,                   KC_RPRN, YL_RCBR, YL_RBRC, YL_GT,   YL_SLSH, _______,
                               _______, YL_ENT, _______,                    _______, _______, _______
),

// both of closest thumbs moved together inward from home, function keys
[THUMBS_INWARD] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_EQL,  KC_MINS, _______,                   _______, KC_PLUS, _______, _______, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

// macros, right thumb to the right of home
[MACROS] = LAYOUT_split_3x6_3(
    _______, YL_QUIT, YL_WRIT, YL_WSCH, YL_SNIP, _______,                   DM_REC1, DM_REC2, DM_RSTP, _______, _______, _______,
    _______, _______, YL_SSHK, _______, YL_FIAP, _______,                   DM_PLY1, DM_PLY2, UPDIR,   YL_LSTS, _______, _______,
    _______, _______, _______, _______,    LGTM, _______,                   _______, _______, _______, _______, _______, _______,
                               _______,  YL_ENT, _______,                   _______, _______, _______
),

// Keyboard/RGB control. bootloader mode. debugging. Screen brightness
// Generally, also, things that you don't type very often or need rarely
// https://docs.qmk.fm/features/rgblight#keycodes
[UTIL] = LAYOUT_split_3x6_3(
    QK_BOOT, _______, DT_UP  , _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, KC_BRID, DT_DOWN, KC_BRIU, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, DT_PRNT, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

// thumbs outward and together
[SYMBOLS] = LAYOUT_split_3x6_3(
    _______, _______, _______, KC_PLUS, KC_UNDS, _______,                   _______, _______, _______, _______, _______, _______,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_PIPE, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, YL_ENT,  _______,                   _______, _______, _______
),

// upper-right key that I never use.
[CRYPT] = LAYOUT_split_3x6_3(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,                   _______, _______, _______
),

/* [LED] = LAYOUT_split_3x6_3( */
/*     _______, _______, _______, _______, _______, _______,                   RM_VALD, UG_VALD, UG_VALU, RM_VALU, _______, _______, */
/*     _______, _______, _______, _______, _______, _______,                   RM_PREV, UG_PREV, UG_NEXT, RM_NEXT, _______, _______, */
/*     _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*                                _______, _______, _______,                   _______, _______, _______ */
/* ), */
  /*   [3] = LAYOUT_split_3x6_3( */
  /* //,-----------------------------------------------------.                    ,-----------------------------------------------------. */
  /*     QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
  /* //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
  /*     RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
  /* //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
  /*     RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
  /* //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
  /*                                         KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT */
  /*                                     //`--------------------------'  `--------------------------' */
  /* ) */
};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, LTHUMB_2R, RTHUMB_2L, THUMBS_INWARD); // both thumbs inward
  state = update_tri_layer_state(state, LTHUMB_2R, MACROS, UTIL);  // both thumbs to the right
  return state;
}

#ifdef OLED_ENABLE

static void render_logo(void) {
  static const char PROGMEM logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};

    oled_write_P(logo, false);
}

static void render_status(void);

bool oled_task_user(void) {
    if (is_keyboard_master()) {
      render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
      render_logo();  // Renders a static logo
    }
    return false;
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


#endif
