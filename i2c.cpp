/*
 * Copyright 2017 NXP
 * Copyright 2024 Tedd OKANO
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */

extern "C" {
#include <stdio.h>
#include <string.h>
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
}

#include	"i2c.h"


#ifdef	CPU_MCXN947VDF
#define EXAMPLE_I2C_MASTER_BASE			(LPI2C2_BASE)
#define LPI2C_MASTER_CLOCK_FREQUENCY 	CLOCK_GetLPFlexCommClkFreq(2u)
#define EXAMPLE_I2C_MASTER				((LPI2C_Type *)EXAMPLE_I2C_MASTER_BASE)
#else
#define EXAMPLE_I2C_MASTER_BASE			LPI2C0
#define LPI2C_MASTER_CLOCK_FREQUENCY	CLOCK_GetLpi2cClkFreq()
#define EXAMPLE_I2C_MASTER				((LPI2C_Type *)EXAMPLE_I2C_MASTER_BASE)
#endif



I2C::I2C( uint32_t frequency )
{
	lpi2c_master_config_t	masterConfig;

	LPI2C_MasterGetDefaultConfig( &masterConfig );
	masterConfig.baudRate_Hz	= frequency;
	LPI2C_MasterInit( EXAMPLE_I2C_MASTER, &masterConfig, LPI2C_MASTER_CLOCK_FREQUENCY );
}

I2C::~I2C() {}

status_t I2C::write( uint8_t address, const uint8_t *dp, int length, bool stop )
{
	status_t	r = kStatus_Fail;
	size_t		txCount	= 0xFFU;

	if ( (r = LPI2C_MasterStart( EXAMPLE_I2C_MASTER, address, kLPI2C_Write )) )
		return r;

	LPI2C_MasterGetFifoCounts(EXAMPLE_I2C_MASTER, NULL, &txCount);
	while (txCount)
	{
		LPI2C_MasterGetFifoCounts(EXAMPLE_I2C_MASTER, NULL, &txCount);
	}

	if ( LPI2C_MasterGetStatusFlags( EXAMPLE_I2C_MASTER ) & kLPI2C_MasterNackDetectFlag )
		return kStatus_LPI2C_Nak;

	if ( (r	= LPI2C_MasterSend( EXAMPLE_I2C_MASTER, (uint8_t *)dp, length )) )
	{
		if ( r == kStatus_LPI2C_Nak )
			LPI2C_MasterStop( EXAMPLE_I2C_MASTER );

		return r;
	}

	if ( stop )
		return LPI2C_MasterStop( EXAMPLE_I2C_MASTER );

	return kStatus_Success;
}


status_t I2C::read( uint8_t address, uint8_t *dp, int length, bool stop )
{
	status_t	r = kStatus_Fail;
	size_t		txCount	= 0xFFU;

	if ( (r = LPI2C_MasterStart( EXAMPLE_I2C_MASTER, address, kLPI2C_Read )) )
		return r;

	do {
		LPI2C_MasterGetFifoCounts( EXAMPLE_I2C_MASTER, NULL, &txCount );
	} while ( txCount );

	if ( LPI2C_MasterGetStatusFlags( EXAMPLE_I2C_MASTER ) & kLPI2C_MasterNackDetectFlag )
		return kStatus_LPI2C_Nak;

	if ( (r	= LPI2C_MasterReceive( EXAMPLE_I2C_MASTER, dp, length )) )
		return r;

	if ( stop )
		return LPI2C_MasterStop( EXAMPLE_I2C_MASTER );

	return kStatus_Success;
}






status_t I2C::reg_write( uint8_t targ, uint8_t reg, const uint8_t *dp, int length )
{
	uint8_t	bp[ REG_RW_BUFFER_SIZE ];
	
	bp[ 0 ]	= reg;
	memcpy( (uint8_t *)bp + 1, (uint8_t *)dp, length );

	last_status	= write( targ, bp, length + 1 );
	
	return last_status;
}

status_t I2C::reg_write( uint8_t targ, uint8_t reg, uint8_t data )
{
	return write( targ, &data, sizeof( data ) );
}

status_t I2C::reg_read( uint8_t targ, uint8_t reg, uint8_t *dp, int length )
{
	last_status	= write( targ, &reg, sizeof( reg ), NO_STOP );
	
	if ( kStatus_Success != last_status )
		return last_status;
	
	return read( targ, dp, length );
}

uint8_t I2C::reg_read( uint8_t targ, uint8_t reg )
{
	last_status	= write( targ, reg, NO_STOP );
	return read( targ );
}

status_t I2C::write( uint8_t targ, uint8_t data, bool stop )
{
	return write( targ, &data, sizeof( data ), stop );
}

uint8_t I2C::read( uint8_t targ, bool stop )
{
	uint8_t	data;

	last_status	= read( targ, &data, sizeof( data ), stop );

	return data;
}


status_t I2C::ccc_set( uint8_t ccc, uint8_t addr, uint8_t data )
{
	return kStatus_Success;
}

status_t I2C::ccc_get( uint8_t ccc, uint8_t addr, uint8_t *dp, uint8_t length )
{
	memset( dp, 0, length );
	return kStatus_Success;
}
