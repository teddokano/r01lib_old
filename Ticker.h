/*
 * Copyright 2024 Tedd OKANO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_TICKER_H
#define R01LIB_TICKER_H

#include <functional>

extern "C" {
#include	"fsl_utick.h"
}


class Ticker
{	
public:
	enum{
		repeat	= kUTICK_Repeat
	};
	Ticker();
	~Ticker();
	
	void	attach( utick_callback_t callback, float sec );

private:
	UTICK_Type	*utick_type;
};

#endif // R01LIB_TICKER_H
