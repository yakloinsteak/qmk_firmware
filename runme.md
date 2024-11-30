# Setup QMK

```
qmk setup -H $HOME/prj/qmk_firmware

lsusb

qmk compile -kb annepro2/c18 -km default

qmk config user.keyboard=annepro2/c18
OR
qmk config user.keyboard=lily58/rev1

qmk config user.keymap=yakloinsteak

qmk new-keymap

qmk compile -kb annepro2/c18 -km yakloinsteak
make annepro2/c18:yakloinsteak
make lily58/rev1:yakloinsteak

n $HOME/prj/qmk_firmware/keyboards/annepro2/keymaps/yakloinsteak/keymap.c

n -p /home/blackman/prj/qmk/keyboards/lily58/keymaps/yakloinsteak/keymap.c \
  /home/blackman/prj/qmk/keyboards/lily58/keymaps/yakloinsteak/rules.mk

qmk compile
```

# annepro2 tools for flashing

sudo apt-get install libusb-1.0-0-dev
git clone https://github.com/OpenAnnePro/AnnePro2-Tools
cd AnnePro2-Tools
devbox add cargo
cargo build --release
copy built binary to /usr/local/bin

# LEDs firmware

git clone https://github.com/OpenAnnePro/annepro2-shine.git --recursive
cd annepro2-shine
make C18
echo hold esc while plugging keyboard in
annepro2_tools --boot -t led build/annepro2-shine-C18.bin

# Flashing

Unplug your keyboard, hold down the top or bottom left key (usually Escape or
Left Control) and plug in your keyboard

qmk flash

# obinskit pre-upgrade
   2.22 application processor,
   2.18 light processor,
   2.02 bluetooth processor
