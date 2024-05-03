// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │Esc│Tab│MO1│Bsp│
     * ├───┼───┼───┼───┤
     * │Num│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │ 0     │ . │   │
     * └───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_6x4(
        KC_ESC,  KC_TAB,  MO(1),   KC_BSPC,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,            KC_PDOT, KC_PENT
    ),

    [1] = LAYOUT_numpad_6x4(
        KC_MUTE,   RGB_TOG, _______, _______,
        _______,   RGB_SPD, RGB_SPI, RGB_VAD,
        _______,   _______, _______,
        _______,  RGB_RMOD, RGB_MOD, RGB_VAI,
        _______,   _______, _______,
        _______,            _______, KC_PENT
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(C(G(KC_LEFT)), C(G(KC_RIGHT))), ENCODER_CCW_CW(G(KC_MINS), G(KC_EQL))},
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(C(G(KC_LEFT)), C(G(KC_RIGHT))), ENCODER_CCW_CW(G(KC_MINS), G(KC_EQL))}
};
#endif

