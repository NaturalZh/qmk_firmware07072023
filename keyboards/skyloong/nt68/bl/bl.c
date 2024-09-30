// Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

bool dis_breath = 0;

void suspend_power_down_kb(void) {
    gpio_write_pin_high(KEY_STATUS_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    gpio_write_pin_low(KEY_STATUS_PIN);
    suspend_wakeup_init_user();
}
bool shutdown_kb(bool jump_to_bootloader) {
    gpio_write_pin_high(KEY_STATUS_PIN);
    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
       case BL_TOGG:
         if (record->event.pressed) {
            if (is_backlight_breathing() && get_backlight_level()){
               dis_breath = 1;
               backlight_disable_breathing();
               backlight_enable();

            } else if (dis_breath && !is_backlight_enabled()){
                backlight_enable_breathing();
                dis_breath = 0;
              }
            return true;
           }

      case BL_BRTG:
        if (record->event.pressed) {
          if (dis_breath || !is_backlight_enabled()){
              return false;
            }
             return true;
        }

       case BL_UP:
           dis_breath = 0;
         return true;

       case BL_DOWN:
           if (record->event.pressed){
               if(dis_breath || !(is_backlight_enabled())) {
                 return false;
                }
           }
         return true;

      default:
        if (record->event.pressed) {
            gpio_write_pin_high(KEY_STATUS_PIN);
        } else {
            gpio_write_pin_low(KEY_STATUS_PIN);
        }
        return true;
    }
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    gpio_set_pin_output(KEY_STATUS_PIN);
    gpio_write_pin_low(KEY_STATUS_PIN);
}
