// Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

int FN_ON = 0;
bool WIN_LOCK = 0;
bool FN_WIN = 0;
bool FN_MAC = 0;
bool L_WIN = 0;
bool L_MAC = 0;

#if defined(RGB_MATRIX_ENABLE)  /*&& defined(CAPS_LOCK_INDEX)*/
const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to aw20216 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, CS3_SW1,   CS2_SW1,   CS1_SW1},
    {0, CS6_SW1,   CS5_SW1,   CS4_SW1},
    {0, CS9_SW1,   CS8_SW1,   CS7_SW1},
    {0, CS12_SW1,   CS11_SW1,   CS10_SW1},

    {0, CS3_SW2,   CS2_SW2,   CS1_SW2},
    {0, CS6_SW2,   CS5_SW2,   CS4_SW2},
    {0, CS9_SW2,   CS8_SW2,   CS7_SW2},
    {0, CS12_SW2,   CS11_SW2,   CS10_SW2},

    {0, CS3_SW3,   CS2_SW3,   CS1_SW3},
    {0, CS6_SW3,   CS5_SW3,   CS4_SW3},
    {0, CS9_SW3,   CS8_SW3,   CS7_SW3},

    {0, CS3_SW4,   CS2_SW4,   CS1_SW4},
    {0, CS6_SW4,   CS5_SW4,   CS4_SW4},
    {0, CS9_SW4,   CS8_SW4,   CS7_SW4},
    {0, CS12_SW4,   CS11_SW4,   CS10_SW4},

    {0, CS3_SW5,   CS2_SW5,   CS1_SW5},
    {0, CS6_SW5,   CS5_SW5,   CS4_SW5},
    {0, CS9_SW5,  CS8_SW5,  CS7_SW5},

    {0, CS3_SW6,  CS2_SW6,  CS1_SW6},
    {0, CS9_SW6,  CS8_SW6,  CS7_SW6},
    {0, CS12_SW6,  CS11_SW6,  CS10_SW6}
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_INDEX, 0, 0, 0);
        }
    }
    return true;
}
#endif

void suspend_power_down_kb(void) {
    gpio_write_pin_low(AW20216S_EN_PIN_1);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    gpio_write_pin_high(AW20216S_EN_PIN_1);
    suspend_wakeup_init_user();
}
bool shutdown_kb(bool jump_to_bootloader) {
    gpio_write_pin_low(AW20216S_EN_PIN_1);
    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#    ifdef RGB_MATRIX_ENABLE
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
         return false;
#    endif
    case RGB_VAI:
      rgb_matrix_set_flags(LED_FLAG_ALL);  //Turn on the LED effect.
      return true;

    default:
      return true;
    }
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
#    ifdef RGB_MATRIX_ENABLE
    gpio_set_pin_output(AW20216S_EN_PIN_1);
    gpio_write_pin_high(AW20216S_EN_PIN_1);
#   endif
}
