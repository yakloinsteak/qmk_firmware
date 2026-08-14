#include QMK_KEYBOARD_H
#include "mykeycodes.h"
#include "mylayers.h"
#include "mymouse.h"
#include "print.h"

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

   register_code(KC_LCTL); // Change the key to be held here
   unregister_code(KC_LCTL); // Change the key that was held here, too!
 */

// TODO: include outside of git
/* #define KEY {0xf8,0x64,0x69,0x2b,0x16,0xe2,0x14,0x94,0xa,0x12} */
/* #define CYPHERTEXT {0x9b,0x8,0xc,0x4a,0x64,0x96,0x71,0xec,0x7e,0x12} */
/* #define CYPHERLENGTH 10 */

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t tmux_timer;
    static bool tmux_on = false;
    static bool lth3_pressed = false;
    static bool rth3_pressed = false;
    static bool lth3_held_with_combo = false;

    /* static char cleartext[CYPHERLENGTH]; */
    /* static char key[] = KEY; */
    /* static char cyphertext[] = CYPHERTEXT; */

#if defined(CONSOLE_ENABLE) && defined(KEYCODE_STRING_ENABLE)
    dprintf("KL: kc: 0x%04X, str: %s, col: %2u, row: %2u, pressed: %u, time: %5u, count: %u\n", keycode, get_keycode_string(keycode), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.count);
#endif

    // Suppress the auto-^a prefix while LTH3+RTH3 is held (symbols-combo mode), and
    // also for the RTH3 press itself (which arrives before rth3_pressed is updated below).
    if (tmux_on && timer_elapsed(tmux_timer) >= TMUX_PREFIX_HOLD_TERM && record->event.pressed
        && keycode != MO(MACROS)
        && !(lth3_pressed && rth3_pressed)) {
        tap_code16(C(KC_A));
    }

    if (keycode == YL_CTLA)           lth3_pressed = record->event.pressed;
    else if (keycode == MO(MACROS))   rth3_pressed = record->event.pressed;

    if (lth3_pressed && rth3_pressed) { layer_on(THUMBS_OUTWARD); lth3_held_with_combo = true; }
    else                                layer_off(THUMBS_OUTWARD);

    switch (keycode) {
    /* case YL_ZUZU: */
    /*     // ./crypt.rb */
    /*     if (record->event.pressed) { */
    /*         // TODO: decrypt once */
    /*        for(int x = 0; x < CYPHERLENGTH; x++) cleartext[x] = key[x] ^ cyphertext[x]; */
    /*        SEND_STRING(cleartext); */
    /*     } */
    /*     break; */
    case YL_CTLA:
        if (record->event.pressed) {
            tmux_timer = timer_read();
            tmux_on = true;
            lth3_held_with_combo = false;
        } else {
            // Suppress the tap-^a when RTH3 was held at any point during this LTH3 hold —
            // it was a brief LTH3+RTH3 combo press, not a single-tap.
            if (timer_elapsed(tmux_timer) < TMUX_PREFIX_HOLD_TERM && !lth3_held_with_combo) { tap_code16(C(KC_A)); }
            tmux_on = false;
        }
        return false;
    case YL_SNIP:
        if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"Z"SS_DELAY(150)"snippets"SS_TAP(X_ENT)); }
        break;
    case YL_QUIT:
        // neovim quit
        if (record->event.pressed) { SEND_STRING(SS_TAP(X_ESC)":wq"SS_TAP(X_ENT)); }
        break;
    case YL_WRIT:
        // neovim write
        if (record->event.pressed) { SEND_STRING(SS_TAP(X_ESC)":w"SS_TAP(X_ENT)); }
        break;
    /* case YL_FIAP: */
    /*     // firefox insecure approve */
    /*     if (record->event.pressed) { send_string_with_delay("\t\t\t " SS_DELAY(400) "\t\t\t\t ", 100); } */
    /*     break; */
    /* case YL_WSCH: */
    /*     // sessionx in tmux but with choices for new session */
    /*     if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"s" SS_DELAY(20) SS_DOWN(X_LCTL)"x"SS_UP(X_LCTL)); } */
    /*     break; */
    case YL_ENT:
        if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LALT)"l"SS_UP(X_LCTL)SS_UP(X_LALT)"\n"); }
        break;
    case YL_LSTS:
        // last session in tmux
        if (record->event.pressed) { SEND_STRING(SS_DOWN(X_LCTL)"a"SS_UP(X_LCTL)"L"); }
        break;
    case YL_SSHK:
        // last session in tmux
        if (record->event.pressed) { SEND_STRING("eval `ssh-agent`;ssh-add"); }
        break;
    case UPDIR:
        if (record->event.pressed) { SEND_STRING("../"); }
        return false; // skip any further pipeline processing which wouldn't be happening for custom keys anyway
        /* break; */
    case DBLCLK:  // Double click the left mouse button.
        if (record->event.pressed) { SEND_STRING(SS_TAP(X_BTN1) SS_DELAY(50) SS_TAP(X_BTN1)); }
        return false;
    case LGTM:  // Looks good to me.
        if (record->event.pressed) { SEND_STRING("LGTM!"); }
        return false;
    case YL_SLSH:
        if (record->event.pressed) { tap_code16(KC_SLSH); }
        return false;
    case YL_LT:
        if (record->event.pressed) { tap_code16(KC_LT); }
        return false;
    case YL_LBRC:
        if (record->event.pressed) { tap_code16(KC_LBRC); }
        return false;
    case YL_LCBR:
        if (record->event.pressed) { tap_code16(KC_LCBR); }
        return false;
    case YL_RCBR:
        if (record->event.pressed) { tap_code16(KC_RCBR); }
        return false;
    case YL_RBRC:
        if (record->event.pressed) { tap_code16(KC_RBRC); }
        return false;
    case YL_GT:
        if (record->event.pressed) { tap_code16(KC_GT); }
        return false;
    case YL_BSLS:
        if (record->event.pressed) { tap_code16(KC_BSLS); }
        return false;
    case YL_BACK:
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_SHIFT) {
              tap_code16(KC_DEL);
            } else {
              tap_code16(KC_BSPC);
            }
        }
        return false;

    case KC_Q: {
        // Ctrl+GUI+Q locks the Mac host from inside the Parallels VM: break out of
        // the VM's input grab, park the cursor on the host, then send the macOS
        // lock chord. Needs BOTH mods -- a plain get_mods() & (CTRL|GUI) is true for
        // *either* one, which fired the whole macro on a bare GUI+Q.
        uint8_t mods = get_mods();
        if (!(record->event.pressed && (mods & MOD_MASK_CTRL) && (mods & MOD_MASK_GUI))) {
            return true;  // handle like a normal Q otherwise
        }

        // Parallels' release-input hotkey is a *bare* Ctrl+Alt. The Ctrl+GUI still
        // physically held here is on the wire, so just adding Alt makes the host see
        // Ctrl+Alt+Cmd and the grab never lifts. Drop every mod, let the host see the
        // all-clear as its own report, then press a clean Ctrl+Alt.
        clear_weak_mods();
        clear_oneshot_mods();
        clear_mods();
        send_keyboard_report();
        wait_ms(VM_RELEASE_CLEAR_MS);

        register_mods(MOD_BIT_LCTRL | MOD_BIT_LALT);
        wait_ms(VM_RELEASE_HOLD_MS);
        unregister_mods(MOD_BIT_LCTRL | MOD_BIT_LALT);

        warp_mouse_move_px(0,-520);

        // Mods are deliberately left cleared: the host is about to lock, and
        // re-asserting the still-held Ctrl+GUI would land on the lock screen.
        tap_code16(G(C(KC_Q)));
        return false;
    }

    // Mouse warping: jump to the left / center / right physical monitor.
    case YL_WRPL:
        if (record->event.pressed) {
            warp_mouse_to_screen(YL_SCREEN_LEFT);
        }
        return false;
    case YL_WRPC:
        if (record->event.pressed) {
            warp_mouse_to_screen(YL_SCREEN_CENTER);
        }
        return false;
    case YL_WRPR:
        if (record->event.pressed) {
            warp_mouse_to_screen(YL_SCREEN_RIGHT);
        }
        return false;
    case YL_WRPB:
        // Warp to the Bitwarden MFA click point. The dialog is centered on the
        // monitor it opens on (which screen depends on the layout), so warp to
        // that monitor's center then nudge by a per-layout offset. +x right,
        // +y down (negate for up). Tune each offset once, on each setup, by eye.
        if (record->event.pressed) {
            switch (mon_layout_get()) {
                case MON_LAPTOP: // the only screen
                    warp_mouse_to_screen(YL_SCREEN_LEFT);   warp_mouse_move_px(330, -220); break;
                case MON_HOME:   // laptop is on the right; dialog opens on the left monitor
                    warp_mouse_to_screen(YL_SCREEN_LEFT);   warp_mouse_move_px(550, -300); break; // TODO: tune
                case MON_OFFICE: // center monitor
                    warp_mouse_to_screen(YL_SCREEN_CENTER); warp_mouse_move_px(550, -350); break;
            }
        }
        return false;
    // Per-key warp (WARP layer): jump the cursor to the desktop point that
    // mirrors this key's physical position. The target table is board-specific
    // (keyed by matrix row/col via each keymap's yl_warp_target override).
    case YL_WARP:
        if (record->event.pressed) {
            uint16_t t = yl_warp_target(record->event.key.row, record->event.key.col);
            warp_mouse_desktop_frac((uint8_t)(t >> 8), (uint8_t)(t & 0xFF));
        }
        return false;
    case YL_MON1:
        if (record->event.pressed) { mon_layout_set(MON_LAPTOP); }
        return false;
    case YL_MON2:
        if (record->event.pressed) { mon_layout_set(MON_HOME); }
        return false;
    case YL_MON3:
        if (record->event.pressed) { mon_layout_set(MON_OFFICE); }
        return false;

    }

  return true;
}
