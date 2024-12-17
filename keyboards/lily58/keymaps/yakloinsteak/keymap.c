#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"

enum {
    HRM_CHORD,
    HRM_ACHORDION,
    HRM_LAYER_STICKY,
};

#if HRM == HRM_ACHORDION
#include "features/achordion.h"
#endif

// ********************************************************************************************************** //
// ************************************************* Tap Dancing ******************************************** //
// ********************************************************************************************************** //

enum {
  TD_QUOT,
};

// https://docs.qmk.fm/features/tap_dance#how-to-use
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ', twice for two quotes and a backspace
    [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, MAGIC_QUOTE),
};

// *************************************************************************************************** //
// ************************************************* Core ******************************************** //
// *************************************************************************************************** //

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY/Base layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Tb/FN |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   | <- tab activates tab-hold layer when held
 k |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |ctlesc|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   | <- magic quotes when double tapped
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |sh/ent| <- right shift act as enter. left double-tap does caps-word
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |util  |      |lowerL| /bkspace/       \Space \  |upperL|      |      | <--- lower/upper layer together is another layer
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[BASE] = LAYOUT(
    KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    YL_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    YL_ESC,   YL_A,   YL_S,    YL_D,    YL_F,    KC_G,                     KC_H,    YL_J,    YL_K,    YL_L,    YL_SCLN, TD_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, YL_RSFT,
                         TG(UTIL), KC_NO, TL_LOWR, KC_BSPC ,  KC_SPC, TL_UPPR, _______, _______
),

/* Tab hold
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  | F9   | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |  =   |      |      |                    |      | home | pgup | ins  | print| F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| left | down |  up  | right|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | end  | pgdn |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[TAB_HOLD_LAYER] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______,                   _______, KC_HOME, KC_PGUP, KC_INS,  KC_PSCR, KC_F12,
    _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* left thumb layer / symbols
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   ~  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

#if HRM == HRM_LAYER_STICKY
[LOWER] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, ST_LALT ,ST_LCTL ,ST_LSFT ,ST_LGUI, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______
),
#else
[LOWER] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                               _______, _______, _______, _______, _______,  _______, _______, _______
),
#endif


/* right thumb / Digits and math
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |  /   |  *   |                    |   ^  |   +  |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  0   |  1   |   2  |  3   |  4   |  5   |-------.    ,-------|   6  |   7  |   8  |   9  |  0   |      |
 * |------+------+------+------+------+------|   (   |    |   )   |------+------+------+------+------+------|
 * |      |      |      |      |  =   |  |   |-------|    |-------|   &  |   -  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \ SPC  \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
#if HRM == HRM_LAYER_STICKY
[UPPER] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, ST_RGUI ,ST_RSFT ,ST_RCTL ,ST_RALT, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______
),
#else
[UPPER] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               XXXXXXX, XXXXXXX, RRRRRRR, XXXXXXX, _______, RRRRRRR, XXXXXXX, _______
),
#endif

/* MOUSE/GUI when both lower/upper layer keys are pressed.
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  WU  |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  WL  |  WD  |  WR  |      |      |-------.    ,-------| Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX, MS_ACL2, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, MS_WHLL, MS_WHLD, MS_WHLR, MS_ACL1, XXXXXXX,                   MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, MS_ACL0, XXXXXXX, DBLCLK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, XXXXXXX, RRRRRRR, MS_BTN1, MS_BTN2, RRRRRRR, XXXXXXX, XXXXXXX
),

/* Slack
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \ SPC  \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
/* [SLACK] = LAYOUT( */
/*   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
/*                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______ */
/* ), */

// ^a before all key-presses
// See process_record_user
/* [TMUX] = LAYOUT( */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
/*                              _______, _______, _______, _______, _______, _______, _______, _______ */
/* ), */

/* [] = LAYOUT( */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, */
/*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
/*                              _______, _______, _______, _______, _______, _______, _______, _______ */
/* ), */

// Keyboard/RGB control. bootloader mode. debugging. screen brightness
// https://docs.qmk.fm/features/rgblight#keycodes
[UTIL] = LAYOUT(
    QK_BOOT, _______, _______, _______, _______, _______,                   UG_TOGG, _______, _______, _______, _______, _______,
    _______, _______, DT_UP  , _______,  _______, _______,                  _______, _______, _______, _______, _______, _______,
    _______, KC_BRID, DT_DOWN, KC_BRIU, _______, _______,                   UG_PREV, UG_VALD, UG_VALU, UG_NEXT, _______, _______,
    _______, _______, DT_PRNT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

};

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*   return update_tri_layer_state(state, SYM, FN1, MS); */
/* } */

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE


/* tap_code(kc) to tap an individual key
   register_code(kc) and unregister_code(kc) to press down and release a key.

   record->event.pressed is true if the event is a press (key down), and false if it is a release (key up).

   record->event.time is a 16-bit timestamp in units of milliseconds of when the event occurred

   record->event.key.row and record->event.key.col are the matrix position of the key, counting from 0.

   If the event comes from a mod-tap (MT) or layer-tap (LT) key, then
   record->tap.count is zero if the key is considered held, otherwise it is
   considered tapped (see also Intercepting Mod-Taps and Achordion).

   get_mods() returns a bitfield of which modifiers are currently active, and
   similarly get_oneshot_mods() for one-shot modifiers (see also Checking
   Modifier State and the next section, Macros that respond to mods).

   Get the layer associated with the key event:
   uint8_t layer = read_source_layers_cache(record->event.key);

   IS_LAYER_ON(layer) returns whether layer is currently on, and

   get_highest_layer(layer_state) returns the highest layer that is currently
   on (see also Working with Layers).

   get_repeat_key_count() indicates whether the key is being invoked through
   Repeat Key or Alternate Repeat Key (see also Repeat Key functions).
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#   if HRM == HRM_ACHORDION
    if (!process_achordion(keycode, record)) { return false; }
#   endif

    /* if (IS_LAYER_ON(TMUX) && record->event.pressed) { */
    /*     tap_code16(C(KC_A));  // Tap Ctrl+A. */
    /* } */

    if (record->event.pressed) {
#ifdef OLED_ENABLE
      set_keylog(keycode, record);
#endif
      // set_timelog();
    }

    switch (keycode) {
    case SNIPPETS:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"Z"SS_DELAY(100)"snippets"SS_TAP(X_ENT));
        }
        break;

    case SWITCH_WINDOW:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"s");
        }
        break;

    case MAGIC_QUOTE:
        if (record->event.pressed) {
            SEND_STRING("''\b");
            /* if ( (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT))) { */
            /*    SEND_STRING("\"\"\b"); */
            /* } else { */
            /*    SEND_STRING("''\b"); */
            /* } */
        }
        break;

    case UPDIR:
        if (record->event.pressed) {
           SEND_STRING("../");
        }
        return false; // skip any further pipeline processing which wouldn't be happening for custom keys anyway
        /* break; */

    case DBLCLK:  // Double click the left mouse button.
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_BTN1) SS_DELAY(50) SS_TAP(X_BTN1));
        }
        return false;
    }

  return true;
}

#if HRM == HRM_ACHORDION
void matrix_scan_user(void) {
  achordion_task();
}
#endif

// ********************************************************************************************************** //
// ************************************************* Chords ************************************************* //
// ********************************************************************************************************** //

const uint16_t PROGMEM ctrla_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM tmux_window_switch_combo[] = {KC_A, KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM snippets_combo[] = {KC_K, KC_L, COMBO_END};

#if HRM == HRM_CHORD
#   define LTHUMB KC_BSPC
#   define RTHUMB KC_SPC
    const uint16_t PROGMEM hrm1l[4][3] = {
        {LTHUMB, KC_F, COMBO_END},
        {LTHUMB, KC_D, COMBO_END},
        {LTHUMB, KC_S, COMBO_END},
        {LTHUMB, KC_A, COMBO_END},
    };
    const uint16_t PROGMEM hrm1r[4][3] = {
        {RTHUMB, KC_J, COMBO_END},
        {RTHUMB, KC_K, COMBO_END},
        {RTHUMB, KC_L, COMBO_END},
        {RTHUMB, KC_SCLN, COMBO_END},
    };
    const uint16_t PROGMEM hrm2l[6][4] = {
        {LTHUMB, KC_F, KC_D, COMBO_END},
        {LTHUMB, KC_F, KC_S, COMBO_END},
        {LTHUMB, KC_F, KC_A, COMBO_END},
        {LTHUMB, KC_D, KC_S, COMBO_END},
        {LTHUMB, KC_D, KC_A, COMBO_END},
        {LTHUMB, KC_S, KC_A, COMBO_END}
    };
    const uint16_t PROGMEM hrm2r[6][4] = {
        {RTHUMB, KC_J, KC_K, COMBO_END},
        {RTHUMB, KC_J, KC_L, COMBO_END},
        {RTHUMB, KC_J, KC_SCLN, COMBO_END},
        {RTHUMB, KC_K, KC_L, COMBO_END},
        {RTHUMB, KC_K, KC_SCLN, COMBO_END},
        {RTHUMB, KC_L, KC_SCLN, COMBO_END}
    };
#endif

combo_t key_combos[] = {
    COMBO(ctrla_combo, LCTL(KC_A)),  // SD send ^a
    COMBO(snippets_combo, SNIPPETS), // snippets in tmux
    COMBO(tmux_window_switch_combo, SWITCH_WINDOW), // common switch window

#   if HRM == HRM_CHORD
        // Single mods
        COMBO(hrm1l[0], KC_LGUI),
        COMBO(hrm1l[1], KC_LSFT),
        COMBO(hrm1l[2], KC_LCTL),
        COMBO(hrm1l[3], KC_LALT),
        COMBO(hrm1r[0], KC_RGUI),
        COMBO(hrm1r[1], KC_RSFT),
        COMBO(hrm1r[2], KC_RCTL),
        COMBO(hrm1r[3], KC_RALT),

        // Dual mods
        COMBO(hrm2l[0], G(KC_LSFT)),
        COMBO(hrm2l[1], G(KC_LCTL)),
        COMBO(hrm2l[2], G(KC_LALT)),
        COMBO(hrm2l[3], S(KC_LCTL)),
        COMBO(hrm2l[4], S(KC_LALT)),
        COMBO(hrm2l[5], C(KC_LALT)),
        COMBO(hrm2r[0], G(KC_RSFT)),
        COMBO(hrm2r[1], G(KC_RCTL)),
        COMBO(hrm2r[2], G(KC_RALT)),
        COMBO(hrm2r[3], S(KC_RCTL)),
        COMBO(hrm2r[4], S(KC_RALT)),
        COMBO(hrm2r[5], C(KC_RALT))
#   endif
};

