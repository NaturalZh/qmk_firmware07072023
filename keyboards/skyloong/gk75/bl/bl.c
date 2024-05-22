//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

int FN_ON = 0;
bool WIN_LOCK = 0;
bool DIS_BRETH = 0;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
       case MO(1):
          if (record->event.pressed) {
            FN_ON = 1;
          } else {
            FN_ON = 0;
          }
          return true;

       case MO(2):
           if (record->event.pressed) {
             FN_ON = 1;
           } else {
             FN_ON = 0;
           }
          return true;

       case MO(3):
           if (record->event.pressed) {
             FN_ON = 1;
           } else {
             FN_ON = 0;
           }
          return true;

       case KC_LGUI:
           if (FN_ON){
              if ( record->event.pressed){
                 WIN_LOCK = !WIN_LOCK ; //change win lock state
                }
              if (!WIN_LOCK) {
                 return false; //windows key locked do nothing
                }
            }
           if (WIN_LOCK) {
               return false; //windows key locked do nothing
            }
           return true;  // continue all further processing of this key

       case TO(0):
           set_single_persistent_default_layer(0);
           return true;

       case TO(1):
           set_single_persistent_default_layer(1);
           return true;

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

void suspend_power_down_kb() {
    suspend_power_down_user();
}

void suspend_wakeup_init_kb() {
    suspend_wakeup_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    return true;
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
}

