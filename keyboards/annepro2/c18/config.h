/*
 * Copyright (c) 2018 Charlie Waters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "pin_defs.h"

#define LINE_UART_TX B0
#define LINE_UART_RX B1

#define LINE_BT_UART_TX A4  // Master TX, BLE RX
#define LINE_BT_UART_RX A5  // Master RX, BLE TX

// Obins stock firmware has something similar to this already enabled, but disabled by default in QMK
#define PERMISSIVE_HOLD

// SPI configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A0
#define SPI_MOSI_PIN A1
#define SPI_MISO_PIN A2

// Flash configuration
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN A3
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 16
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SECTOR_SIZE 4096
#define EXTERNAL_FLASH_BLOCK_SIZE 4096
#define EXTERNAL_FLASH_SIZE (256 * 1024) // 2M-bit flash size

#define TAPPING_TOGGLE 2

// https://docs.qmk.fm/tap_hold
// If you're getting the mod of the mod-tap behavior accidentially: increase
// adjust on the fly for debug/testing on layer fn2 up/down/x
#define TAPPING_TERM 210
#define TAPPING_TERM_PER_KEY

// https://docs.qmk.fm/tap_hold#permissive-hold
// hitting another key before tap timeout will do the hold action, but you
// cannot release the first key within tapping term.
// #define PERMISSIVE_HOLD
//
// Similar, but if you release the first key and still want the hold action:
// These can be fine-tuned per key if needed. See https://docs.qmk.fm/tap_hold#hold-on-other-key-press
#define HOLD_ON_OTHER_KEY_PRESS

#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY 5 //Delay between pressing a movement key and cursor movement
#define MOUSEKEY_INTERVAL 10 //Time between cursor movements in milliseconds
#define MOUSEKEY_MOVE_DELTA 16 //Step size for accelerating from initial to base speed
#define MOUSEKEY_INITIAL_SPEED 100 //Initial speed of the cursor in pixel per second
#define MOUSEKEY_BASE_SPEED 5000 //Maximum cursor speed at which acceleration stops
#define MOUSEKEY_DECELERATED_SPEED 400 // Decelerated cursor speed
#define MOUSEKEY_ACCELERATED_SPEED 3000 // Accelerated cursor speed
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16 //Initial number of movements of the mouse wheel
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32 //Maximum number of movements at which acceleration stops
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
