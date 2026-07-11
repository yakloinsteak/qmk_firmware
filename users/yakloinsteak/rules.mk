COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes       # Audio control and System control (brightness/app key/etc.)
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
DYNAMIC_TAPPING_TERM_ENABLE = yes
TRI_LAYER_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes

CONSOLE_ENABLE = yes
KEYCODE_STRING_ENABLE = yes

# Unicode
UNICODE_COMMON = yes
UNICODE_ENABLE = yes

SRC += combos.c
SRC += tap_hooks.c
SRC += process_record_user.c
SRC += mymouse.c
SRC += myoled.c
SRC += mylayers.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tapdance.c
endif
