/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_SPI_H
#define R01LIB_SPI_H

extern "C" {
#include "fsl_lpspi.h"
}

#include	"spi.h"

#define	SPI_FREQ		1000000UL


class SPI
{
public:
	SPI( uint32_t frequency = SPI_FREQ, uint8_t mode = 0 );
	~SPI();
	
	virtual status_t	write( uint8_t *wp, uint8_t *rp, int length );
	status_t	last_status;

private:
};

#endif // R01LIB_SPI_H
