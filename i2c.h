/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_I2C_H
#define R01LIB_I2C_H

extern "C" {
#include <string.h>
#include "fsl_lpi2c.h"
}


#include	"i2c.h"

#define	I2C_FREQ		400000UL

#define	STOP			true
#define	NO_STOP			false

#define	REG_RW_BUFFER_SIZE				10


class I2C
{
public:
	I2C( uint32_t frequency = I2C_FREQ );
	~I2C();
	
	virtual status_t	reg_write( uint8_t targ, uint8_t reg, const uint8_t *dp, int length );
	virtual status_t	reg_write( uint8_t targ, uint8_t reg, uint8_t data );
	
	virtual status_t	reg_read( uint8_t targ, uint8_t reg, uint8_t *dp, int length );
	virtual uint8_t		reg_read( uint8_t targ, uint8_t reg );
	
	virtual status_t	write( uint8_t address, const uint8_t *dp, int length, bool stop = STOP );
	virtual status_t	write( uint8_t targ, uint8_t data, bool stop = STOP );
	
	virtual status_t	read( uint8_t address, uint8_t *dp, int length, bool stop = STOP );
	virtual uint8_t		read( uint8_t targ, bool stop = STOP );

	virtual status_t	ccc_set( uint8_t ccc, uint8_t addr, uint8_t data );
	virtual status_t	ccc_get( uint8_t ccc, uint8_t addr, uint8_t *dp, uint8_t length );

	status_t	last_status;

private:
};

#endif // R01LIB_I2C_H
