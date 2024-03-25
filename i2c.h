/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_I2C_H
#define R01LIB_I2C_H

/** I3C class
 *	
 *  @class I3C
 *
 *	A class for demonstrating I3C bus
 */

extern "C" {
#include	<string.h>
#include	"fsl_lpi2c.h"
}

#define	I2C_FREQ			400000UL

#define	STOP				true
#define	NO_STOP				false

#define	REG_RW_BUFFER_SIZE	10

class I2C
{
public:
	
	/** Create an I2C instance with specified pins
	 *
	 * @param sda pin number to connect SDA
	 * @param scl pin number to connect SCL
	 * @param no_hw (option) flag for I3C. I3C constructor will set this flag to avoid set hardware for both I3C and I2C
	 */
	I2C( int sda, int scl, bool no_hw = false );

	/** Destractor to freeing I3C resource
	 */
	~I2C();
	
	/** set SCL frequency
	 *
	 * @param frequency integer value in "Hz"
	 */
	virtual void		frequency( uint32_t frequency );

	/** Register write (multiple byte data)
	 *	provideds interface for register write
	 *	
	 * @param targ target address
	 * @param reg register address
	 * @param dp data to write
	 * @param length data length
	 * @return status_t
	 */
	virtual status_t	reg_write( uint8_t targ, uint8_t reg, const uint8_t *dp, int length );

	/** Register write (single byte data)
	 *	provideds interface for register write
	 *	
	 * @param targ target address
	 * @param reg register address
	 * @param data data to write
	 * @return status_t
	 */
	virtual status_t	reg_write( uint8_t targ, uint8_t reg, uint8_t data );
	
	/** Register read (multiple byte data)
	 *	provideds interface for register read
	 *	
	 * @param targ target address
	 * @param reg register address
	 * @param dp data to write
	 * @param length data length
	 * @return status_t
	 */
	virtual status_t	reg_read( uint8_t targ, uint8_t reg, uint8_t *dp, int length );

	/** Register read (single byte data)
	 *	provideds interface for register read
	 *	returns a single byte data
	 *	status can be checked by last_status variable
	 *	
	 * @param targ target address
	 * @param reg register address
	 * @return read data
	 */
	virtual uint8_t		reg_read( uint8_t targ, uint8_t reg );
	
	/** write transactiond (multiple byte data)
	 *
	 * @param targ target address
	 * @param dp data to write
	 * @param length data length
	 * @param stop (option) generate STOP condition: "false" to make repeated-start in next transaction
	 * @return status_t
	 */
	virtual status_t	write( uint8_t address, const uint8_t *dp, int length, bool stop = STOP );

	/** write transactiond (single byte data)
	 *
	 * @param targ target address
	 * @param data data to write
	 * @param stop (option) generate STOP condition: "false" to make repeated-start in next transaction
	 * @return status_t
	 */
	virtual status_t	write( uint8_t targ, uint8_t data, bool stop = STOP );
	
	/** read transactiond (multiple byte data)
	 *
	 * @param targ target address
	 * @param dp data to write
	 * @param length data length
	 * @param stop (option) generate STOP condition: "false" to make repeated-start in next transaction
	 * @return status_t
	 */
	virtual status_t	read( uint8_t address, uint8_t *dp, int length, bool stop = STOP );

	/** read transaction (single byte data)
	 *	provideds interface for register read
	 *	returns a single byte data
	 *	status can be checked by last_status variable
	 *
	 * @param targ target address
	 * @param stop (option) generate STOP condition: "false" to make repeated-start in next transaction
	 * @return data
	 */
	virtual uint8_t		read( uint8_t targ, bool stop = STOP );

	/** method for I3C class compatibility (dummy method)
	 * does notheing but return kStatus_Success
	 * 
	 * @param ccc CCC command
	 * @param data single byte data
	 * @return kStatus_Success
	 */
	virtual status_t	ccc_set( uint8_t ccc, uint8_t addr, uint8_t data );

	/** method for I3C class compatibility (dummy method)
	 * does notheing but clearing data buffer and return kStatus_Success
	 *  
	 * @param ccc CCC command
	 * @param dp data to send
	 * @param length data length
	 * @return status_t
	 */
	virtual status_t	ccc_get( uint8_t ccc, uint8_t addr, uint8_t *dp, uint8_t length );

	/** variable for reporting last state */
	status_t				last_status;
	
private:
	lpi2c_master_config_t	masterConfig;
};

#endif // R01LIB_I2C_H
