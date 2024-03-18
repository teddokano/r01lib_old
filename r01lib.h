/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_R01LIB_H
#define R01LIB_R01LIB_H

extern "C" {
#include	"fsl_debug_console.h"
}

#include	"i3c.h"
#include	"i2c.h"
#include	"spi.h"
#include	"io.h"
#include	"Ticker.h"
#include	"InterruptIn.h"
#include	"mcu.h"
#include	"P3T1755.h"

#define	r01lib_start	__attribute__((constructor)) void start_mcu() { init_mcu(); PRINTF("\r\n***  MCU initialized properly  ***\r\n"); }

#endif // R01LIB_R01LIB_H
