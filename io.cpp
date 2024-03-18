/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include	"fsl_gpio.h"

#include	"mcu.h"
#include	"io.h"

typedef	struct	_gpio_pin {
	GPIO_Type	*base;
	uint32_t	pin;
} gpio_pin;

static gpio_pin pins[]	= {
	{ D0_GPIO,  D0_GPIO_PIN  },
	{ D1_GPIO,  D1_GPIO_PIN  },
	{ D2_GPIO,  D2_GPIO_PIN  },
	{ D3_GPIO,  D3_GPIO_PIN  },
	{ D4_GPIO,  D4_GPIO_PIN  },
	{ D5_GPIO,  D5_GPIO_PIN  },
	{ D6_GPIO,  D6_GPIO_PIN  },
	{ D7_GPIO,  D7_GPIO_PIN  },
	{ D8_GPIO,  D8_GPIO_PIN  },
	{ D9_GPIO,  D9_GPIO_PIN  },
	{ D10_GPIO, D10_GPIO_PIN },
	{ D11_GPIO, D11_GPIO_PIN },
	{ D12_GPIO, D12_GPIO_PIN },
	{ D13_GPIO, D13_GPIO_PIN },
	{ D18_GPIO, D18_GPIO_PIN },
	{ D19_GPIO, D19_GPIO_PIN },
	{ A0_GPIO,  A0_GPIO_PIN  },
	{ A1_GPIO,  A1_GPIO_PIN  },
	{ A2_GPIO,  A2_GPIO_PIN  },
	{ A3_GPIO,  A3_GPIO_PIN  },
	{ A4_GPIO,  A4_GPIO_PIN  },
	{ A5_GPIO,  A5_GPIO_PIN  },
	{ SW2_GPIO,  SW2_GPIO_PIN  }
};

extern "C" {
#include "fsl_debug_console.h"
}


DigitalInOut::DigitalInOut( uint8_t pin_num, bool direction, bool v )
	: _pn( pin_num ), _dir( direction ), _value( v )
{
	if ( NULL == pins[ _pn ].base )
		return;
	
	gpio_pin_config_t led_config = { (gpio_pin_direction_t)direction, _value };
	
	gpio_n		= pins[ _pn ].base;
	gpio_pin	= pins[ _pn ].pin;
	
	GPIO_PinInit( gpio_n, gpio_pin, &led_config );
	value( (bool)_value );
}

DigitalInOut::~DigitalInOut(){}

void DigitalInOut::value( bool value )
{
	if ( NULL == pins[ _pn ].base )
		return;

	if ( kGPIO_DigitalOutput == _dir )
		GPIO_PinWrite( gpio_n, gpio_pin, value );
	
	_value	= value;
}

bool DigitalInOut::value( void )
{
	if ( NULL == pins[ _pn ].base )
		return 0;

	if ( kGPIO_DigitalInput == _dir )
		return GPIO_PinRead( gpio_n, gpio_pin );
	else
		return _value;
}

void DigitalInOut::output( void )
{
	_dir	= kGPIO_DigitalOutput;
}

void DigitalInOut::input( void )
{
	_dir	= kGPIO_DigitalInput;
}

DigitalInOut& DigitalInOut::operator=( bool v )
{
	value( v );
	return *this;
}

DigitalInOut& DigitalInOut::operator=( DigitalInOut& )
{
	return *this;
}

DigitalInOut::operator bool()
{
	return value();
}

DigitalOut::DigitalOut( uint8_t pin_num, bool value )
	: DigitalInOut( pin_num, kGPIO_DigitalOutput, value )
{
}

DigitalOut::~DigitalOut() {}

DigitalIn::DigitalIn( uint8_t pin_num )
	: DigitalInOut( pin_num, kGPIO_DigitalInput, 0 )
{
}

DigitalIn::~DigitalIn() {}

