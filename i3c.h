/*
 * Copyright 2022 NXP
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This code based on a sample projects: 
 *    "frdmmcxa153_i3c_master_read_sensor_p3t1755" from SDK_2.14.2_FRDM-MCXA153 and 
 *    "lpcxpresso860max_i3c_master_read_sensor_icm42688p" from SDK_2.15.000_LPCXpresso860MAX
 */

#ifndef R01LIB_I3C_H
#define R01LIB_I3C_H


#include "i2c.h"

#include "fsl_i3c.h"

#define I3C_BROADCAST_ADDR		0x7E
#define	PID_LENGTH				6

//#define	LOWER_SCL_FREQ

#ifdef	LOWER_SCL_FREQ
#define I3C_OD_FREQ		1500000UL
#define I3C_PP_FREQ		4000000UL
#else
#define I3C_OD_FREQ		4000000UL
#define I3C_PP_FREQ		12500000UL
#endif //HIGHER_SCL_FREQ

enum CCC
{
	BROADCAST_ENEC		= 0x00,
	BROADCAST_RSTDAA	= 0x06,
	BROADCAST_ENTDAA	= 0x07,
	DIRECT_ENEC			= 0x80,
	DIRECT_DICEC		= 0x81,
	DIRECT_SETDASA		= 0x87,
	DIRECT_SETNEWDA		= 0x88,
	DIRECT_GETPID		= 0x8D,
	DIRECT_GETBCR		= 0x8E,
	DIRECT_GETDCR		= 0x8F,
	DIRECT_GETSTATUS	= 0x90,
	DIRECT_RSTACT		= 0x90
};

typedef void (*i3c_func_ptr)(void); 

class I3C : public I2C
{
public:
	I3C( uint32_t i2c_freq = I2C_FREQ, uint32_t i3c_od_freq = I3C_OD_FREQ, uint32_t i3c_pp_freq = I3C_PP_FREQ );
	~I3C();
	
	status_t	write( uint8_t targ, const uint8_t *dp, int length, bool stop = STOP );	
	status_t	read( uint8_t targ, uint8_t *dp, int length, bool stop = STOP );
	
	uint8_t		check_IBI( void );
	void		set_IBI_callback( i3c_func_ptr fp );

	status_t	ccc_broadcast( uint8_t ccc, const uint8_t *dp, uint8_t length );
	status_t	ccc_set( uint8_t ccc, uint8_t addr, uint8_t data );
	status_t	ccc_get( uint8_t ccc, uint8_t addr, uint8_t *dp, uint8_t length );

	static void		master_ibi_callback( I3C_Type *base, i3c_master_handle_t *handle, i3c_ibi_type_t ibiType, i3c_ibi_state_t ibiState );
	static void		master_callback( I3C_Type *base, i3c_master_handle_t *handle, status_t status, void *userData );

private:
	status_t	xfer( i3c_direction_t dir, i3c_bus_type_t type, uint8_t targ, uint8_t *dp, int length, bool stop = STOP );
	
	static const	i3c_master_transfer_callback_t	masterCallback;
};

#endif // R01LIB_I3C_H
