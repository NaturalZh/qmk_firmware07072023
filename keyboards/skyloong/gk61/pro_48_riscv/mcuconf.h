// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef GD32_I2C_USE_I2C0
#define GD32_I2C_USE_I2C0 TRUE

// #undef STM32_I2C_USE_DMA
// #define STM32_I2C_USE_DMA TRUE
    