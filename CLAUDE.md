# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository orientation

This is a personal fork of [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware). The active branch is `dev` (not `master`); `master` tracks upstream. `origin` is `yakloinsteak/qmk_firmware`, `upstream` is `qmk/qmk_firmware`.

Personal work lives in three places — everything else is upstream QMK code:

- `users/yakloinsteak/` — the personal userspace. Shared C across all the user's keymaps: custom keycodes (`mykeycodes.h`), layer enum (`mylayers.h`), combos, [Achordion](https://getreuer.info/posts/keyboards/achordion/) integration, tap-dance, and `process_record_user`. Each keymap's `rules.mk` picks up `SRC += ...` from here.
- `keyboards/<kb>/keymaps/yakloinsteak/` for `annepro2/c18`, `lily58/rev1`, `crkbd/rev1`. These keymaps `#include "mykeycodes.h"` / `"mylayers.h"` etc. from the userspace.
- `keyboards/annepro2/keymaps/yakloinsteak-offset/` — a layout variant of the annepro2 keymap (different physical layout, same userspace).
- `bigrams` (root file) — text list of letter pairs that don't trigger home-row mod misfires. Reference when tuning HRM / Achordion behavior.
- `runme.md` — the user's own scratch notes on setup/flashing for these boards.

When adding a custom keycode, layer, combo, or behavior used by more than one keymap, add it to `users/yakloinsteak/` rather than duplicating in each keymap. Keymap files should stay thin (layout tables + small board-specific tweaks).

## Build, flash, test

`qmk` CLI and `make` both work; the user's notes (`runme.md`) prefer:

```
qmk compile -kb annepro2/c18 -km yakloinsteak
make annepro2/c18:yakloinsteak       # equivalent
make lily58/rev1:yakloinsteak
make crkbd/rev1:yakloinsteak
qmk flash                            # uses configured user.keyboard/user.keymap
```

To target a specific keymap without `qmk config`: pass `-kb` and `-km` explicitly, or use the `kb:km` make target form.

Board-specific flashing:

- **annepro2**: held-Esc bootloader, flashed with `annepro2_tools` (from OpenAnnePro). Output `.bin` files in repo root were built and copied out for flashing.
- **lily58 yakloinsteak** sets `CONVERT_TO=elite_pi` (RP2040). Flash via UF2: mount `/dev/sda1` at `/media/blackman/RPI-RP2` and copy `.build/lily58_rev1_yakloinsteak.uf2` — see `load-lilly`.
- **crkbd yakloinsteak** is currently configured without `CONVERT_TO` (AVR build).

### Unit tests

QMK has C-level unit tests under `tests/`:

```
make test:all                        # run everything
make test:<test_name>                # single test, e.g. test:basic
```

Python-side CLI tests use nose2 (`nose2.cfg`, `requirements-dev.txt`).

### Build artifacts

`.build/` (and stray `*.hex`/`*.bin`/`*.uf2` in the repo root from earlier flashes) are not committed. The `annepro2_c18_yakloinsteak-offset.bin` etc. in the root are kept on disk for convenience but aren't sources.

## Personal keymap architecture

Layer enum (`users/yakloinsteak/mylayers.h`): `BASE, TAB_HOLD_LAYER, LOWER, UPPER, ADJUST, MACROS, UTIL, SYMBOLS, CRYPT`. Keymaps reference these by name; reordering the enum reorders every keymap.

Key mechanisms in use, all wired through the userspace:

- **Home-row mods** (`YL_A`, `YL_S`, `YL_D`, `YL_F` and mirrors) — MT-based, gated by **Achordion** (`users/yakloinsteak/achordion.c`, from Pascal Getreuer) to suppress same-hand mod activations. `ACHORDION_STREAK` is on. The `bigrams` file is the manual reference list for pairs that should *not* hit a mod.
- **Tap-dance** (`tapdance.c/h`) — gated by `TAP_DANCE_ENABLE = yes` in each keymap's `rules.mk`. `YL_GRAV` / `YL_QUOT` are `TD(...)` only when enabled; the userspace `#ifdef`s around this.
- **Combos** (`combos.c/h`) — `COMBO_TERM = 35`, `COMBO_ENABLE = yes`.
- **Tri-layer** — `LOWER + UPPER → ADJUST` via QMK's built-in `TRI_LAYER_ENABLE`.
- **Custom keycodes** start at `SAFE_RANGE` in `mykeycodes.h` (`YL_SNIP`, `YL_WSCH`, `UPDIR`, `DBLCLK`, `LGTM`, …). Handlers live in `users/yakloinsteak/process_record_user.c`. **Always add new keycodes to the `enum custom_keycodes`** there, not in individual keymaps.
- **OLED on lily58** — `lib/keylogger.c` (and on the full variant: `rgb_state_reader`, `layer_state_reader`, `logo_reader`, `timelogger`) are added via the keymap's `rules.mk`.

`users/yakloinsteak/config.h` holds the cross-board tuning: `TAPPING_TERM 205`, `PERMISSIVE_HOLD`, `BOTH_SHIFTS_TURNS_ON_CAPS_WORD`, mouse-key acceleration, unicode modes. Per-keymap `config.h` files are deliberately small overrides.

## Upstream contribution rules (only relevant when sending PRs to qmk/qmk_firmware)

`.github/copilot-instructions.md` is the QMK project's PR-review checklist. Highlights for if you ever upstream changes:

- **New keyboards → `master`**, everything else (refactors, core, keyboard updates, moves) → **`develop`**. Never PR from your fork's `master`.
- **Personal keymaps are no longer accepted upstream** — only `default` and `default_<vendor>` keymaps. The `yakloinsteak` keymaps are not upstream-eligible.
- Use `#pragma once`, not `#ifndef` guards. No direct GPIO/I2C/SPI; use QMK abstractions. Use `wait_ms()` / `timer_read()` (not `_delay_ms()`).
- Validate keyboard configs with `qmk lint -kb <keyboard>` and `qmk format-json -i path/to/info.json` before submitting.
- VID+PID combinations must be unique across the whole `keyboards/` tree; check with `grep -r '"vid"' keyboards/` before picking new ones.

For changes to this fork that are *not* going upstream (i.e. the yakloinsteak keymaps and userspace), these rules don't apply — just keep changes on `dev`.

## Toolchain

`devbox.json` pins the dev shell: `qmk`, Python 3.13, `cargo`, `rustc`, `avrdudess`. A `devbox shell` activates a venv where `pip install qmk` lives. If a `qmk` command fails with import errors, suspect the venv isn't sourced.
