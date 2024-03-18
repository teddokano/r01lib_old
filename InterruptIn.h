/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_INTERRUPTIN_H
#define R01LIB_INTERRUPTIN_H

extern "C" {
#include	"fsl_utick.h"
}

#include	"io.h"

typedef	void (*func_ptr)( void );

class InterruptIn : public DigitalIn
{	
public:
	InterruptIn( uint8_t pin_num );
	~InterruptIn();
	
	void	rise( func_ptr callback );
	void	fall( func_ptr callback );
	void	regist( func_ptr callback, gpio_interrupt_config_t type );
};

#endif // R01LIB_INTERRUPTIN_H
