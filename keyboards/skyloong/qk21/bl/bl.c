// Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

bool DIS_BRETH = 0;

bool led_update_kb(led_t led_state) {
    gpio_set_pin_output_open_drain(B10);
    bool res = led_update_user(led_state);
    if(res) {
        gpio_write_pin(B10, !led_state.num_lock);
    }
    return res;
}

void suspend_power_down_kb(void) {
    gpio_write_pin_low(BACKLIGHT_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    suspend_wakeup_init_user();
}
bool shutdown_kb(bool jump_to_bootloader) {
    gpio_write_pin_low(BACKLIGHT_PIN);
    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
       case BL_TOGG:
           if (record->event.pressed){
               if(is_backlight_breathing()) {
                    backlight_disable_breathing();
                    DIS_BRETH = 1;

                }else if(DIS_BRETH && !(is_backlight_enabled())){
                    backlight_enable_breathing();
                    DIS_BRETH = 0;
                }
           }
         return true;

       case BL_BRTG:
           if (record->event.pressed){
               if(DIS_BRETH || !(is_backlight_enabled())) {
                 return false;
                }
           }
         return true;

       case BL_UP:
           DIS_BRETH = 0;
         return true;

       case BL_DOWN:
           if (record->event.pressed){
               if(DIS_BRETH || !(is_backlight_enabled())) {
                 return false;
                }
           }
         return true;

      default:
         return true;
    }
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
}
