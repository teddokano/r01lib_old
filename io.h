/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_IO_H
#define R01LIB_IO_H

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#define	PIN_OUTPUT			kGPIO_DigitalOutput
#define	PIN_INPUT			kGPIO_DigitalInput

#define	DISABLED_GPIO		(GPIO_Type *)NULL
#define	DISABLED_PIN		0xFF

#ifdef	CPU_MCXN947VDF
	#define A0_GPIO				DISABLED_GPIO
	#define A1_GPIO				DISABLED_GPIO
	#define A2_GPIO				GPIO0
	#define A3_GPIO				GPIO0
	#define A4_GPIO				GPIO0
	#define A5_GPIO				GPIO0
	#define D0_GPIO				GPIO4
	#define D1_GPIO				GPIO4
	#define D2_GPIO				GPIO0
	#define D3_GPIO				GPIO1
	#define D4_GPIO				GPIO0
	#define D5_GPIO				GPIO1
	#define D6_GPIO				GPIO1
	#define D7_GPIO				GPIO0
	#define D8_GPIO				GPIO0
	#define D9_GPIO				GPIO0
	#define D10_GPIO			GPIO0
	#define D11_GPIO			GPIO0
	#define D12_GPIO			GPIO0
	#define D13_GPIO			GPIO0
	#define D18_GPIO			GPIO4
	#define D19_GPIO			GPIO4
	#define SW2_GPIO			D5_GPIO
	#define SW3_GPIO			GPIO0

	#define A0_GPIO_PIN			DISABLED_PIN
	#define A1_GPIO_PIN			DISABLED_PIN
	#define A2_GPIO_PIN			14U
	#define A3_GPIO_PIN			22U
	#define A4_GPIO_PIN			15U
	#define A5_GPIO_PIN			23U
	#define D0_GPIO_PIN			3U
	#define D1_GPIO_PIN			2U
	#define D2_GPIO_PIN			29U
	#define D3_GPIO_PIN			23U
	#define D4_GPIO_PIN			30U
	#define D5_GPIO_PIN			21U
	#define D6_GPIO_PIN			2U
	#define D7_GPIO_PIN			31U
	#define D8_GPIO_PIN			28U
	#define D9_GPIO_PIN			10U
	#define D10_GPIO_PIN		27U
	#define D11_GPIO_PIN		24U
	#define D12_GPIO_PIN		26U
	#define D13_GPIO_PIN		25U
	#define D18_GPIO_PIN		0U
	#define D19_GPIO_PIN		1U
	#define SW2_GPIO_PIN		A5_GPIO_PIN
	#define SW3_GPIO_PIN		6

	#define	RED		D9
	#define	GREEN	D10
	#define	BLUE	D6

#else // CPU_MCXN947VDF

	#define D0_GPIO				GPIO1
	#define D1_GPIO				GPIO1
	#define D2_GPIO				GPIO2
	#define D3_GPIO				GPIO3
	#define D4_GPIO				GPIO2
	#define D5_GPIO				GPIO3
	#define D6_GPIO				GPIO3
	#define D7_GPIO				GPIO3
	#define D8_GPIO				GPIO3
	#define D9_GPIO				GPIO3
	#define D10_GPIO			GPIO2
	#define D11_GPIO			GPIO2
	#define D12_GPIO			GPIO2
	#define D13_GPIO			GPIO2
	#define D18_GPIO			GPIO1
	#define D19_GPIO			GPIO1
	#define SW2_GPIO			GPIO3
	#define SW3_GPIO			GPIO1
	#define A0_GPIO				GPIO1
	#define A1_GPIO				GPIO1
	#define A2_GPIO				GPIO1
	#define A3_GPIO				GPIO2
	#define A4_GPIO				GPIO3
	#define A5_GPIO				GPIO3

	#define D0_GPIO_PIN			4U
	#define D1_GPIO_PIN			5U
	#define D2_GPIO_PIN			4U
	#define D3_GPIO_PIN			0U
	#define D4_GPIO_PIN			5U
	#define D5_GPIO_PIN			12U
	#define D6_GPIO_PIN			13U
	#define D7_GPIO_PIN			1U
	#define D8_GPIO_PIN			15U
	#define D9_GPIO_PIN			14U
	#define D10_GPIO_PIN		6U
	#define D11_GPIO_PIN		13U
	#define D12_GPIO_PIN		16U
	#define D13_GPIO_PIN		12U
	#define D18_GPIO_PIN		8U
	#define D19_GPIO_PIN		9U
	#define SW2_GPIO_PIN		29U
	#define SW3_GPIO_PIN		7U
	#define A0_GPIO_PIN			10U
	#define A1_GPIO_PIN			12U
	#define A2_GPIO_PIN			13U
	#define A3_GPIO_PIN			0U
	#define A4_GPIO_PIN			31U
	#define A5_GPIO_PIN			30U

	#define	RED		D5
	#define	GREEN	D6
	#define	BLUE	D3


#endif // CPU_MCXN947VDF

enum { 	D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D18, D19,
		A0, A1, A2, A3, A4, A5, SW2, SW3 };

#define	PIN_LED_OFF	true
#define	PIN_LED_ON	false

class DigitalInOut
{
public:
	DigitalInOut( uint8_t pin_num, bool direction = kGPIO_DigitalInput, bool value = 0 );
	~DigitalInOut();
	
	void	value( bool value );
	bool	value( void );
	
	void	output( void );
	void	input( void );
	
	/** A short hand for setting pins
	 */
	DigitalInOut&	operator=( bool v );
	DigitalInOut&	operator=( DigitalInOut& rhs );

	/** A short hand for reading pins
	 */
	operator	bool();

protected:
	uint8_t		_pn; 
	GPIO_Type	*gpio_n;
	uint8_t		gpio_pin; 
	
private:
	bool 	_dir; 
	bool 	_value;
};

class DigitalOut : public DigitalInOut
{
public:
	using DigitalInOut::operator=;

	DigitalOut( uint8_t pin_num, bool value = 0 );
	~DigitalOut();
};

class DigitalIn : public DigitalInOut
{
public:
	using DigitalInOut::operator=;

	DigitalIn( uint8_t pin_num );
	~DigitalIn();
};

#endif // R01LIB_IO_H
