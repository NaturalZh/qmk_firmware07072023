//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#define HC595_ST_PIN B1  //74HC595 storage register clock input
#define HC595_SH_PIN B0  //74HC595 shift register clock input
#define HC595_DS B3   // 74HC595 serial data input
#include "led_hc595.c"
uint8_t IND = 0;  //buffer of LED Display

int FN_ON = 0;
bool WIN_LOCK = 0;
bool dis_breath = 0;

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

    case KC_LGUI:
      if (FN_ON){
          if ( record->event.pressed){
             WIN_LOCK = !WIN_LOCK ; //change win lock state
            }
          if (!WIN_LOCK) {
             IND = IND & (~WINLK_ON);   //Close win lock display
             s_serial_to_parallel(IND);
             return false; //windows key locked do nothing
            }
          s_serial_to_parallel(IND);
        }
      if (WIN_LOCK) {
             IND = IND | WINLK_ON;   //Open win lock display
             s_serial_to_parallel(IND);
             return false; //windows key locked do nothing
            }
      return true;  // continue all further processing of this key

    case TO(0):
       set_single_persistent_default_layer(0);
       return true;

    case TO(1):
       set_single_persistent_default_layer(1);
       return true;

    default:
      return true;
    }
   s_serial_to_parallel(IND);
}

void suspend_power_down_kb() {
    s_serial_to_parallel(0);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb() {
    s_serial_to_parallel(IND);
    suspend_wakeup_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    s_serial_to_parallel(0);
    return true;
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        //switch to win layer display
        IND = IND & (~MAC_ON);
        IND = IND | WIN_ON;
        break;
    case 1:
        //switch to mac layer display
        IND = IND & (~WIN_ON);
        IND = IND | MAC_ON;
        break;
    }
    s_serial_to_parallel(IND);
  return state;
}


bool led_update_kb(led_t led_state) {
    //caps lock display
    if (led_state.caps_lock) {
        IND = IND | CAPS_ON;
    } else {
        IND = IND & (~CAPS_ON);
    }
    //number lock display
    if (led_state.num_lock) {
        IND = IND | NUM_ON;
    } else {
        IND = IND & (~NUM_ON);
    }
    //scroll lock display
    if (led_state.scroll_lock) {
        IND = IND | SCR_ON;
    } else {
        IND = IND & (~SCR_ON);
    }

    s_serial_to_parallel(IND);
    return true;
}


void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    s_serial_to_parallel(0xFF);
    IND = SKYLOONG;
}

