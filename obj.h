/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef R01LIB_BASE_OBJ_H
#define R01LIB_BASE_OBJ_H

/** Obj class
 *	
 *  @class Obj
 *
 *	A base class for all MCU resource using class to make sure the MCU is initialized properly.
 *	All MCU resource using class must derived from this class 
 */

class Obj
{
public:
	/** Create a Obj instance with specified pins
	 *
	 * @param done (option) flag to monitor who call this
	 */

	Obj( bool done = false );
	
	/** Destractor */
	~Obj();
	
private:
	static bool	init_done;
};

#endif // R01LIB_BASE_OBJ_H
