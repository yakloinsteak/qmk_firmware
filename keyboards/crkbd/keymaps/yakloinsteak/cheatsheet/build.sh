#!/usr/bin/env bash
# Regenerate the crkbd yakloinsteak keymap cheat sheet.
# Produces cheatsheet.html (here) and the PDF/PNG in the repo root.
# Requires: node, chromium.  Keep gen.mjs in sync with keymap.c when it changes.
set -euo pipefail
here="$(cd "$(dirname "$0")" && pwd)"
root="$(cd "$here/../../../../.." && pwd)"   # -> repo root
html="$here/cheatsheet.html"
pdf="$root/crkbd-yakloinsteak-cheatsheet.pdf"
png="$root/crkbd-yakloinsteak-cheatsheet.png"

node "$here/gen.mjs"

# Chromium 148 uses --headless=new. Outputs must live under $HOME (snap confinement).
chromium --headless=new --no-sandbox --disable-gpu \
  --no-pdf-header-footer --print-to-pdf="$pdf" "$html"
chromium --headless=new --no-sandbox --disable-gpu --hide-scrollbars \
  --force-device-scale-factor=1 --window-size=2560,1440 \
  --screenshot="$png" "$html"

echo "PDF: $pdf"
echo "PNG: $png  ($(magick identify -format '%wx%h' "$png"))"
