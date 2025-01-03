COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes       # Audio control and System control (brightness/app key/etc.)
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
DYNAMIC_TAPPING_TERM_ENABLE = yes
TRI_LAYER_ENABLE = yes

SRC += achordion.c
SRC += achordion_hooks.c
SRC += combos.c
SRC += tap_hooks.c
SRC += process_record_user.c
