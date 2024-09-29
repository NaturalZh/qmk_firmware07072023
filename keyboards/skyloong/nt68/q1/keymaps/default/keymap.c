// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define WIN_LOCK_INDEX 60

int FN_ON = 0;
bool WIN_LOCK = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
         KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,       KC_8,     KC_9,        KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,    KC_INS,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,       KC_I,     KC_O,        KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,    KC_DEL,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,       KC_K,     KC_L,     KC_SCLN,     KC_QUOT,   KC_ENT,              KC_PGUP,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,     KC_SLSH,     KC_RSFT,    KC_UP,              KC_PGDN,
        KC_LCTL,    MO(1),  KC_LGUI,  KC_LALT,             KC_SPC,                                     KC_RALT,      KC_APP,     KC_LEFT,  KC_DOWN,             KC_RIGHT
    ),

    [1] = LAYOUT(
         KC_GRV,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,      KC_F8,    KC_F9,      KC_F10,      KC_F11,   KC_F12,   _______,   KC_MUTE,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,    _______,  _______,     _______,    RGB_RMOD,  RGB_MOD,   RGB_TOG,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,    _______,  _______,     _______,     _______,  _______,              KC_HOME,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,    _______,  _______,     _______,     _______,   RGB_VAI,              KC_END,
        _______,  _______,  _______,  _______,            _______,                                     _______,     _______,     RGB_SPD,   RGB_VAD,             RGB_SPI
    ),

    [2] = LAYOUT(
         KC_ESC,    KC_1,     KC_2,     KC_3,     KC_4,    KC_5,     KC_6,     KC_7,       KC_8,     KC_9,      KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,    KC_INS,
         KC_TAB,    KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,     KC_Y,     KC_U,       KC_I,     KC_O,      KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,    KC_DEL,
        KC_CAPS,    KC_A,     KC_S,     KC_D,     KC_F,    KC_G,     KC_H,     KC_J,       KC_K,     KC_L,   KC_SCLN,     KC_QUOT,   KC_ENT,              KC_PGUP,
        KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_N,     KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,     KC_RSFT,    KC_UP,              KC_PGDN,
        KC_LCTL,   MO(1),  KC_LALT,  KC_LGUI,            KC_SPC,                                  KC_RGUI,   KC_RALT,     KC_LEFT,  KC_DOWN,             KC_RIGHT
    )

};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (WIN_LOCK) {
        RGB_MATRIX_INDICATOR_SET_COLOR(WIN_LOCK_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_LOCK_INDEX, 0, 0, 0);
        }
    }
    return true;
}


#if defined(DIP_SWITCH_MAP_ENABLE)
const uint16_t PROGMEM dip_switch_map[NUM_DIP_SWITCHES][NUM_DIP_STATES] = {
    DIP_SWITCH_OFF_ON(DF(0), DF(2))
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
    case MO(1):
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

    default:
      return true;
    }
}


