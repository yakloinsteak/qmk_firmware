AUDIO_ENABLE = no           # Audio output
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
COMBO_ENABLE = yes
COMMAND_ENABLE = no         # Commands for debug and configuration
CONSOLE_ENABLE = no         # Console for debug
DIGITIZER_ENABLE = yes
EXTRAKEY_ENABLE = yes       # Audio control and System control (brightness/app key/etc.)
LTO_ENABLE = yes            # Link Time Optimization enabled
MOUSEKEY_ENABLE = yes       # Mouse keys
NKRO_ENABLE = no            # N-Key Rollover
OLED_ENABLE = yes           # OLED display
RGBLIGHT_ENABLE = yes        # Enable WS2812 RGB underlight.

CAPS_WORD_ENABLE = yes

#DYNAMIC_TAPPING_TERM_ENABLE = no
TAP_DANCE_ENABLE = yes

CONVERT_TO=elite_pi

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
