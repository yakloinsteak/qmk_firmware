#!/usr/bin/env node
// Generate a Corne (crkbd/rev1) yakloinsteak keymap cheat sheet as a single
// self-contained HTML file. Screen CSS = 2560x1440 dark wallpaper; @media print
// = portrait Letter. Render with headless chromium (see build.sh).
//
// Source of truth (keep in sync if the keymap changes):
//   keyboards/crkbd/keymaps/yakloinsteak/keymap.c   (layer tables)
//   users/yakloinsteak/mykeycodes.h                 (YL_* defines / mods)
//   users/yakloinsteak/process_record_user.c        (custom keycode behavior)
import { writeFileSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, join } from "node:path";

const OUT = join(dirname(fileURLToPath(import.meta.url)), "cheatsheet.html");

// ---------------------------------------------------------------------------
// Layer tables — 42 keycodes each, in LAYOUT_split_3x6_3 order:
//   row0 (6L,6R), row1 (6L,6R), row2 (6L,6R), thumbs (3L,3R)
// ---------------------------------------------------------------------------
const LAYERS = [
  { name: "Base", hint: "default layer", keys: [
    "YL_TAB","KC_Q","KC_W","KC_E","KC_R","KC_T",  "KC_Y","KC_U","KC_I","KC_O","KC_P","YL_CRPT",
    "YL_ESC","YL_A","YL_S","YL_D","YL_F","KC_G",   "KC_H","YL_J","YL_K","YL_L","YL_SCLN","YL_QUOT",
    "KC_LSFT","KC_Z","KC_X","KC_C","KC_V","KC_B",  "KC_N","KC_M","KC_COMM","KC_DOT","KC_SLSH","YL_RSFT",
    "YL_LTH3","KC_ENT","YL_LTH1",  "YL_RTH1","YL_SPC","YL_RTH3",
  ]},
  { name: "Nav", hint: "hold Tab", keys: [
    "_______","_______","_______","KC_EQL","KC_MINS","_______",  "_______","KC_HOME","KC_PGUP","KC_INS","KC_PSCR","KC_F12",
    "_______","_______","_______","_______","_______","_______",  "KC_LEFT","KC_DOWN","KC_UP","KC_RGHT","KC_BSPC","KC_DEL",
    "_______","_______","_______","_______","_______","_______",  "_______","KC_END","KC_PGDN","_______","_______","_______",
    "_______","_______","_______",  "_______","_______","_______",
  ]},
  { name: "Mouse", hint: "hold left-inner thumb", keys: [
    "XXXXXXX","XXXXXXX","MS_WHLU","XXXXXXX","MS_ACL2","XXXXXXX",  "YL_WRPB","MS_BTN1","MS_BTN2","XXXXXXX","YL_WRPL","XXXXXXX",
    "_______","MS_WHLL","MS_WHLD","MS_WHLR","MS_ACL0","XXXXXXX",  "MS_LEFT","MS_DOWN","MS_UP","MS_RGHT","YL_WRPC","XXXXXXX",
    "_______","XXXXXXX","XXXXXXX","XXXXXXX","MS_ACL1","XXXXXXX",  "DBLCLK","XXXXXXX","XXXXXXX","XXXXXXX","YL_WRPR","XXXXXXX",
    "_______","_______","_______",  "_______","_______","_______",
  ]},
  { name: "Num / Sym", hint: "hold right-inner thumb", keys: [
    "_______","_______","_______","KC_EQL","KC_MINS","_______",  "_______","KC_PLUS","_______","_______","_______","_______",
    "YL_GRAV","YL_1","YL_2","YL_3","YL_4","KC_5",   "KC_6","YL_7","YL_8","YL_9","YL_0","_______",
    "_______","YL_BSLS","YL_LT","YL_LBRC","YL_LCBR","KC_LPRN",  "KC_RPRN","YL_RCBR","YL_RBRC","YL_GT","YL_SLSH","_______",
    "_______","YL_ENT","_______",  "_______","_______","_______",
  ]},
  { name: "Fn", hint: "hold both inner thumbs (tri-layer)", keys: [
    "_______","_______","_______","KC_EQL","KC_MINS","_______",  "_______","KC_PLUS","_______","_______","_______","_______",
    "_______","KC_F1","KC_F2","KC_F3","KC_F4","KC_F5",  "KC_F6","KC_F7","KC_F8","KC_F9","KC_F10","KC_F11",
    "_______","_______","_______","_______","_______","_______",  "_______","_______","_______","_______","_______","_______",
    "_______","_______","_______",  "_______","_______","_______",
  ]},
  { name: "Macros", hint: "hold right-outer thumb, or hold Esc", keys: [
    "_______","YL_QUIT","YL_WRIT","YL_WSCH","YL_SNIP","_______",  "DM_REC1","DM_REC2","DM_RSTP","_______","_______","_______",
    "_______","_______","YL_SSHK","_______","YL_FIAP","_______",  "DM_PLY1","DM_PLY2","UPDIR","YL_LSTS","_______","_______",
    "_______","_______","_______","_______","LGTM","_______",  "_______","_______","_______","_______","_______","_______",
    "_______","YL_ENT","_______",  "_______","_______","_______",
  ]},
  { name: "Util", hint: "left-inner + right-outer thumbs (tri-layer)", keys: [
    "QK_BOOT","_______","DT_UP","_______","_______","_______",  "_______","_______","_______","_______","_______","_______",
    "_______","KC_BRID","DT_DOWN","KC_BRIU","_______","_______",  "_______","YL_MON1","YL_MON2","YL_MON3","_______","_______",
    "_______","_______","DT_PRNT","_______","_______","_______",  "_______","_______","_______","_______","_______","_______",
    "_______","_______","_______",  "_______","_______","_______",
  ]},
  { name: "Symbols", hint: "hold left-inner-outer (⌃A) + right-outer thumbs", keys: [
    "_______","_______","_______","KC_PLUS","KC_UNDS","_______",  "_______","_______","_______","_______","_______","_______",
    "KC_TILD","KC_EXLM","KC_AT","KC_HASH","KC_DLR","KC_PERC",  "KC_CIRC","KC_AMPR","KC_ASTR","KC_LPRN","KC_RPRN","_______",
    "_______","KC_PIPE","_______","_______","_______","_______",  "_______","_______","_______","_______","_______","_______",
    "_______","YL_ENT","_______",  "_______","_______","_______",
  ]},
];

// ---------------------------------------------------------------------------
// Label map.  Each entry: [main, sub, kind]
//   kind: "" normal, "mod" home-row mod-tap, "layer" layer switch,
//         "macro" custom string macro, "trans" transparent, "blank" no-op
// sub is a small badge (mod glyph, hold-layer, or note).
// ---------------------------------------------------------------------------
const A = "⌥", C = "⌃", S = "⇧", G = "⌘"; // Alt Ctrl Shift Gui

const MAP = {
  "_______": ["", "", "trans"],
  "XXXXXXX": ["", "", "blank"],

  // home-row mods — base
  "YL_A": ["A", A, "mod"], "YL_S": ["S", C, "mod"], "YL_D": ["D", S, "mod"], "YL_F": ["F", G, "mod"],
  "YL_J": ["J", G, "mod"], "YL_K": ["K", S, "mod"], "YL_L": ["L", C, "mod"], "YL_SCLN": [";", A, "mod"],
  // home-row mods — numbers
  "YL_1": ["1", A, "mod"], "YL_2": ["2", C, "mod"], "YL_3": ["3", S, "mod"], "YL_4": ["4", G, "mod"],
  "YL_7": ["7", G, "mod"], "YL_8": ["8", S, "mod"], "YL_9": ["9", C, "mod"], "YL_0": ["0", A, "mod"],
  // home-row mods — bracket/slash pairs
  "YL_BSLS": ["\\", A, "mod"], "YL_LT": ["<", C, "mod"], "YL_LBRC": ["[", S, "mod"], "YL_LCBR": ["{", G, "mod"],
  "YL_RCBR": ["}", G, "mod"], "YL_RBRC": ["]", S, "mod"], "YL_GT": [">", C, "mod"], "YL_SLSH": ["/", A, "mod"],

  // layer-tap / layer-hold keys
  "YL_TAB":  ["Tab", "Nav", "layer"],
  "YL_ESC":  ["Esc", "Macros", "layer"],
  "YL_LTH1": ["Mouse", "hold", "layer"],
  "YL_RTH1": ["Num/Sym", "hold", "layer"],
  "YL_RTH3": ["Macros", "hold", "layer"],
  "YL_CRPT": ["Crypt", "hold", "layer"],
  "YL_LTH3": ["⌃A", "tmux", "macro"],
  "YL_SPC":  ["Space", "", ""],
  "YL_RSFT": ["Shift", S, ""],
  "KC_LSFT": ["Shift", S, ""],

  // custom string macros (process_record_user.c)
  "YL_SNIP": ["Snips", "", "macro"],
  "YL_WSCH": ["sess x", "tmux", "macro"],
  "UPDIR":   ["../", "", "macro"],
  "DBLCLK":  ["2×Click", "", "macro"],
  "YL_WRIT": [":w", "nvim", "macro"],
  "YL_QUIT": [":wq", "nvim", "macro"],
  "YL_FIAP": ["FF appr", "", "macro"],
  "YL_LSTS": ["last", "tmux", "macro"],
  "YL_SSHK": ["ssh-add", "", "macro"],
  "LGTM":    ["LGTM!", "", "macro"],
  "YL_ENT":  ["term ⏎", "", "macro"],
  "YL_MON1": ["laptop", "monitor", "macro"],
  "YL_MON2": ["home", "monitor", "macro"],
  "YL_MON3": ["office", "monitor", "macro"],
  "YL_WRPL": ["Warp L", "mouse", "macro"],
  "YL_WRPC": ["Warp C", "mouse", "macro"],
  "YL_WRPR": ["Warp R", "mouse", "macro"],
  "YL_WRPB": ["Warp", "MFA", "macro"],
  "YL_GRAV": ["` ~", "tap-dance", "macro"],
  "YL_QUOT": ["' \"", "tap-dance", "macro"],

  // mouse keys
  "MS_WHLU": ["Wheel ↑", "", ""], "MS_WHLD": ["Wheel ↓", "", ""],
  "MS_WHLL": ["Wheel ←", "", ""], "MS_WHLR": ["Wheel →", "", ""],
  "MS_LEFT": ["←", "move", ""], "MS_RGHT": ["→", "move", ""],
  "MS_UP": ["↑", "move", ""], "MS_DOWN": ["↓", "move", ""],
  "MS_BTN1": ["Click L", "", ""], "MS_BTN2": ["Click R", "", ""],
  "MS_ACL0": ["Accel 0", "slow", ""], "MS_ACL1": ["Accel 1", "", ""], "MS_ACL2": ["Accel 2", "fast", ""],

  // dynamic macros / tapping term / misc firmware
  "DM_REC1": ["Rec 1", "", ""], "DM_REC2": ["Rec 2", "", ""], "DM_RSTP": ["Rec ■", "stop", ""],
  "DM_PLY1": ["Play 1", "", ""], "DM_PLY2": ["Play 2", "", ""],
  "DT_UP": ["Tap +", "term", ""], "DT_DOWN": ["Tap −", "term", ""], "DT_PRNT": ["Tap ?", "print", ""],
  "QK_BOOT": ["BOOT", "flash", "macro"],
  "KC_BRIU": ["Bright +", "", ""], "KC_BRID": ["Bright −", "", ""],

  // named symbols / nav
  "KC_ENT": ["⏎", "", ""], "KC_BSPC": ["⌫", "", ""], "KC_DEL": ["Del", "", ""], "KC_TAB": ["Tab", "", ""],
  "KC_ESC": ["Esc", "", ""], "KC_SPC": ["Space", "", ""],
  "KC_HOME": ["Home", "", ""], "KC_END": ["End", "", ""], "KC_PGUP": ["PgUp", "", ""], "KC_PGDN": ["PgDn", "", ""],
  "KC_INS": ["Ins", "", ""], "KC_PSCR": ["PrtSc", "", ""],
  "KC_LEFT": ["←", "", ""], "KC_RGHT": ["→", "", ""], "KC_UP": ["↑", "", ""], "KC_DOWN": ["↓", "", ""],
  "KC_EQL": ["=", "", ""], "KC_MINS": ["−", "", ""], "KC_PLUS": ["+", "", ""], "KC_UNDS": ["_", "", ""],
  "KC_LPRN": ["(", "", ""], "KC_RPRN": [")", "", ""],
  "KC_TILD": ["~", "", ""], "KC_EXLM": ["!", "", ""], "KC_AT": ["@", "", ""], "KC_HASH": ["#", "", ""],
  "KC_DLR": ["$", "", ""], "KC_PERC": ["%", "", ""], "KC_CIRC": ["^", "", ""], "KC_AMPR": ["&", "", ""],
  "KC_ASTR": ["*", "", ""], "KC_PIPE": ["|", "", ""],
  "KC_COMM": [",", "", ""], "KC_DOT": [".", "", ""], "KC_SLSH": ["/", "", ""], "KC_SCLN": [";", "", ""],
};

const esc = (s) => String(s).replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");

function info(kc) {
  if (MAP[kc]) return { main: MAP[kc][0], sub: MAP[kc][1], kind: MAP[kc][2] };
  // Fn keys and bare letters/digits: strip KC_ prefix.
  const m = kc.replace(/^KC_/, "");
  return { main: m, sub: "", kind: "" };
}

function keyHTML(kc) {
  const { main, sub, kind } = info(kc);
  const cls = ["key", kind].filter(Boolean).join(" ");
  const subHTML = sub ? `<span class="sub">${esc(sub)}</span>` : "";
  return `<div class="${cls}">${subHTML}<span class="main">${esc(main)}</span></div>`;
}

function rowHTML(keys, thumbs = false) {
  const left = keys.slice(0, thumbs ? 3 : 6).map(keyHTML).join("");
  const right = keys.slice(thumbs ? 3 : 6).map(keyHTML).join("");
  const lc = thumbs ? "half thumb l" : "half";
  const rc = thumbs ? "half thumb r" : "half";
  return `<div class="row${thumbs ? " thumbs" : ""}"><div class="${lc}">${left}</div><div class="cgap"></div><div class="${rc}">${right}</div></div>`;
}

function boardHTML(layer) {
  const k = layer.keys;
  const rows = [
    rowHTML(k.slice(0, 12)),
    rowHTML(k.slice(12, 24)),
    rowHTML(k.slice(24, 36)),
    rowHTML(k.slice(36, 42), true),
  ].join("");
  return `<section class="card">
    <h2><span class="lname">${esc(layer.name)}</span><span class="lhint">${esc(layer.hint)}</span></h2>
    <div class="board">${rows}</div>
  </section>`;
}

const legend = `<section class="card legend">
  <h2><span class="lname">Legend</span></h2>
  <div class="legrid">
    <div><span class="chip mod"><span class="sub">${A}</span><span class="main">A</span></span> home-row mod: tap letter, hold modifier</div>
    <div><b>${A}</b> Alt &nbsp; <b>${C}</b> Ctrl &nbsp; <b>${S}</b> Shift &nbsp; <b>${G}</b> Gui/⌘</div>
    <div><span class="chip layer"><span class="sub">hold</span><span class="main">Nav</span></span> hold a thumb/key to reach a layer</div>
    <div><span class="chip macro"><span class="main">:wq</span></span> custom macro / string</div>
    <div><span class="chip trans"></span> transparent (falls through) &nbsp; <span class="chip blank"></span> unused</div>
    <div class="tri">Tri-layers: <b>Mouse+Num/Sym → Fn</b>, &nbsp; <b>Mouse+Macros → Util</b></div>
  </div>
</section>`;

const cards = LAYERS.map(boardHTML).join("\n");

const html = `<!doctype html>
<html lang="en"><head><meta charset="utf-8"><title>Corne — yakloinsteak keymap</title>
<style>
  :root {
    --kw: 56px; --kh: 50px; --gap: 6px; --cgap: 30px;
    --bg: #10141c; --card: #1a2130; --ink: #e7ecf5; --dim: #55627a;
    --mod: #7aa2ff; --layer: #8be0b0; --macro: #f5c26b; --transc: #2a3242;
    --half-w: calc(6 * var(--kw) + 5 * var(--gap));
    font-family: "DejaVu Sans", "Noto Sans", system-ui, sans-serif;
  }
  * { box-sizing: border-box; }
  body { margin: 0; background: var(--bg); color: var(--ink); }
  .page { padding: 26px 30px 30px; min-height: 100vh; display: flex; flex-direction: column; justify-content: center; }
  header.title { display: flex; align-items: baseline; gap: 14px; margin: 0 0 18px; }
  header.title h1 { font-size: 26px; margin: 0; font-weight: 700; letter-spacing: .3px; }
  header.title .sub { color: var(--dim); font-size: 14px; }
  .grid { display: grid; grid-template-columns: repeat(3, 1fr); gap: 20px; }
  .card { background: var(--card); border: 1px solid #26304200; border-radius: 12px; padding: 12px 14px 14px; }
  .card h2 { margin: 0 0 10px; display: flex; align-items: baseline; gap: 8px; }
  .card h2 .lname { font-size: 16px; font-weight: 700; }
  .card h2 .lhint { font-size: 11px; color: var(--dim); font-weight: 500; }
  .board { display: flex; flex-direction: column; gap: var(--gap); }
  .row { display: flex; gap: var(--gap); justify-content: center; }
  .half { display: flex; gap: var(--gap); }
  .cgap { width: var(--cgap); flex: 0 0 var(--cgap); }
  .thumbs { margin-top: 3px; }
  .thumbs .half { width: var(--half-w); }
  .thumbs .half.l { justify-content: flex-end; }
  .thumbs .half.r { justify-content: flex-start; }
  .key {
    position: relative; width: var(--kw); height: var(--kh);
    border-radius: 7px; background: #222c3e; border: 1px solid #313d54;
    display: flex; align-items: center; justify-content: center;
    text-align: center; padding: 1px; overflow: hidden;
  }
  .key .main { font-size: 13px; font-weight: 600; line-height: 1.05; }
  .key .sub {
    position: absolute; top: 2px; right: 4px; font-size: 8.5px;
    color: var(--dim); font-weight: 700; line-height: 1;
  }
  .key.mod { border-color: var(--mod); }
  .key.mod .sub { color: var(--mod); }
  .key.layer { background: #1f3a2e; border-color: var(--layer); }
  .key.layer .main { color: #cbf3dc; font-size: 11px; white-space: normal; overflow-wrap: anywhere; }
  .key.layer .sub { color: var(--layer); }
  .key.macro { background: #33291a; border-color: var(--macro); }
  .key.macro .main { color: #ffe6bc; font-size: 10.5px; }
  .key.macro .sub { color: var(--macro); }
  .key.trans { background: var(--transc); border-color: #232c3c; }
  .key.blank { background: transparent; border-color: #1e2636; border-style: dashed; }
  /* legend */
  .legend .legrid { display: flex; flex-direction: column; gap: 9px; font-size: 12.5px; color: #c3cbdb; }
  .legend .tri { color: var(--ink); }
  .chip {
    position: relative; display: inline-flex; align-items: center; justify-content: center;
    width: 44px; height: 30px; border-radius: 6px; background: #222c3e; border: 1px solid #313d54;
    vertical-align: middle; margin-right: 6px;
  }
  .chip .main { font-size: 12px; font-weight: 600; }
  .chip .sub { position: absolute; top: 1px; right: 3px; font-size: 8px; font-weight: 700; }
  .chip.mod { border-color: var(--mod); } .chip.mod .sub { color: var(--mod); }
  .chip.layer { background: #1f3a2e; border-color: var(--layer); } .chip.layer .sub { color: var(--layer); }
  .chip.macro { background: #33291a; border-color: var(--macro); }
  .chip.trans { background: var(--transc); } .chip.blank { background: transparent; border-style: dashed; }

  /* ---- print: portrait Letter, one page, light background, 2 columns
         (the Corne is 12 cols wide, so 3 boards don't fit portrait) ---- */
  @media print {
    @page { size: letter portrait; margin: 8mm; }
    :root {
      --kw: 26px; --kh: 24px; --gap: 3px; --cgap: 10px;
      --bg: #fff; --card: #f4f6fa; --ink: #101828; --dim: #8a93a6; --transc: #e6eaf1;
    }
    body { background: #fff; }
    .page { padding: 0; min-height: auto; display: block; }
    header.title { margin-bottom: 10px; }
    header.title h1 { font-size: 16px; } header.title .sub { font-size: 10px; }
    .grid { grid-template-columns: repeat(2, 1fr); gap: 8px; }
    .card { border: 1px solid #d7dde8; padding: 6px 8px 7px; break-inside: avoid; }
    .card h2 { margin-bottom: 6px; }
    .card h2 .lname { font-size: 11px; } .card h2 .lhint { font-size: 8px; }
    .key { background: #fff; border-color: #c7cede; border-radius: 5px; }
    .key .main { font-size: 8px; letter-spacing: -0.2px; } .key .sub { font-size: 5.5px; top: 1px; right: 2px; }
    .key.layer { background: #e6f6ec; } .key.layer .main { color: #14683f; font-size: 7.5px; }
    .key.macro { background: #fdf1dc; } .key.macro .main { color: #8a5a12; font-size: 6.5px; }
    .key.trans { background: #edf0f5; border-color: #dfe4ec; } .key.blank { background: #fff; border-color: #eef1f6; }
    .legend .legrid { font-size: 9px; gap: 6px; }
  }
</style></head>
<body><div class="page">
  <header class="title"><h1>Corne — yakloinsteak keymap</h1><span class="sub">crkbd/rev1 · split_3x6_3 · home-row mods (Achordion)</span></header>
  <div class="grid">
    ${cards}
    ${legend}
  </div>
</div></body></html>`;

writeFileSync(OUT, html);
// Report any keycodes that fell through to the raw-strip fallback, so we notice
// unlabeled keys (letters/digits/Fn are expected; YL_*/MS_*/DM_* are not).
const seen = new Set();
for (const L of LAYERS) for (const kc of L.keys) if (!MAP[kc]) seen.add(kc);
const suspicious = [...seen].filter((k) => !/^KC_[A-Z0-9]+$/.test(k));
console.log("wrote", OUT);
if (suspicious.length) console.log("fallback (check these):", suspicious.join(", "));
else console.log("all non-KC keycodes have explicit labels");
