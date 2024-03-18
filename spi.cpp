/*
 * Copyright 2017 NXP
 * Copyright 2024 Tedd OKANO
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */

extern "C" {
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_lpspi.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
}

#include	"spi.h"


#ifdef	CPU_MCXN947VDF
#define EXAMPLE_LPSPI_MASTER_BASEADDR (LPSPI1)
#define EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs0)
#define EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs0)
#define LPSPI_MASTER_CLK_FREQ CLOCK_GetLPFlexCommClkFreq(1u)
#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */
#else
#define EXAMPLE_LPSPI_MASTER_BASEADDR         (LPSPI1)
#define EXAMPLE_LPSPI_MASTER_IRQN             (LPSPI1_IRQn)
#define EXAMPLE_LPSPI_DEALY_COUNT             0xFFFFF
#define LPSPI_MASTER_CLK_FREQ                 (CLOCK_GetLpspiClkFreq(1))
#define EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT     (kLPSPI_Pcs1)
#define EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER (kLPSPI_MasterPcs1)
#define EXAMPLE_LPSPI_MASTER_IRQHandler       (LPSPI1_IRQHandler)
#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */
#endif

SPI::SPI( uint32_t frequency, uint8_t mode )
{
	lpspi_master_config_t masterConfig;

	LPSPI_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate = frequency;
	masterConfig.whichPcs = EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT;
	masterConfig.pcsToSckDelayInNanoSec        = 1000000000U / (masterConfig.baudRate * 2U);
	masterConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / (masterConfig.baudRate * 2U);
	masterConfig.betweenTransferDelayInNanoSec = 1000000000U / (masterConfig.baudRate * 2U);

	masterConfig.cpol	= (lpspi_clock_polarity_t)((mode >> 0) & 0x1);
	masterConfig.cpha	= (lpspi_clock_phase_t   )((mode >> 1) & 0x1);

	LPSPI_MasterInit( EXAMPLE_LPSPI_MASTER_BASEADDR, &masterConfig, LPSPI_MASTER_CLK_FREQ );
}

SPI::~SPI() {}

status_t SPI::write( uint8_t *wp, uint8_t *rp, int length )
{
	lpspi_transfer_t	masterXfer;

	masterXfer.txData		= wp;
	masterXfer.rxData		= rp;
	masterXfer.dataSize		= length;
	masterXfer.configFlags	= EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;

	return LPSPI_MasterTransferBlocking( EXAMPLE_LPSPI_MASTER_BASEADDR, &masterXfer );
}
