# MCU
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52342_ANNEPRO2
MCU_STARTUP = ht32f523xx

BOARD = ANNEPRO2_C18

# Bootloader selection
BOOTLOADER = custom
PROGRAM_CMD = annepro2_tools --boot $(BUILD_DIR)/$(TARGET).bin

# Anne Pro 2
SRC = \
	annepro2_ble.c \
	ap2_led.c \
	protocol.c \
	rgb_driver.c \

COMBO_ENABLE = yes
DIGITIZER_ENABLE = no
DYNAMIC_TAPPING_TERM_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = no
# CONSOLE_ENABEL = yes
