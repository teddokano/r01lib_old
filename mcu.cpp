/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

extern "C" {
#include "peripherals.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_i3c.h"
#include "fsl_lpi2c.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_utick.h"
#include "fsl_clock.h"
#include "fsl_reset.h"
}

#include "mcu.h"

void init_mcu( void )
{
#ifdef	CPU_MCXN947VDF
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom4Clk, 1);
	CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

	/* Attach PLL0 clock to I3C, 150MHz / 6 = 25MHz. */
	CLOCK_SetClkDiv(kCLOCK_DivI3c1FClk, 6U);
	CLOCK_AttachClk(kPLL0_to_I3C1FCLK);

	/* I2C */
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 1u);
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);

	/* SPI */
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom1Clk, 1u);
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM1);

	SYSCON->CLOCK_CTRL |= SYSCON_CLOCK_CTRL_FRO1MHZ_ENA_MASK;	//	UTICK

	CLOCK_EnableClock( kCLOCK_Gpio0 );
	CLOCK_EnableClock( kCLOCK_Gpio1 );
	CLOCK_EnableClock( kCLOCK_Gpio3 );
	CLOCK_EnableClock( kCLOCK_Gpio4 );

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
		/* Init FSL debug console. */
		BOARD_InitDebugConsole();
	#endif

#else
	/* Attach clock to I3C 24MHZ */
	CLOCK_SetClockDiv( kCLOCK_DivI3C0_FCLK, 2U );
	CLOCK_AttachClk( kFRO_HF_DIV_to_I3C0FCLK );

	/* I2C */
	CLOCK_SetClockDiv(kCLOCK_DivLPI2C0, 1u);
	CLOCK_AttachClk(kFRO12M_to_LPI2C0);

	/* SPI */
	CLOCK_SetClockDiv(kCLOCK_DivLPSPI1, 1u);
	CLOCK_AttachClk(kFRO12M_to_LPSPI1);

	CLOCK_EnableClock( kCLOCK_GateGPIO0 );
	CLOCK_EnableClock( kCLOCK_GateGPIO1 );
	CLOCK_EnableClock( kCLOCK_GateGPIO2 );
	CLOCK_EnableClock( kCLOCK_GateGPIO3 );

	RESET_PeripheralReset( kUTICK0_RST_SHIFT_RSTn );
	
	BOARD_InitPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();
	
#endif

	UTICK_Init( UTICK0 );
}

void wait( float delayTime_sec )
{
	SDK_DelayAtLeastUs( (uint32_t)(delayTime_sec * 1000000.0), CLOCK_GetCoreSysClkFreq() );
}

