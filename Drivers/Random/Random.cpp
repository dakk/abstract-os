/*
 * AbastractOS
 * Copyright (C) 2011 Davide Gessa
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "Random.hpp"
#include <arch.h>
#include <Driver.hpp>


/**
 * Create the random driver
 */
RandomDriver::RandomDriver() : Driver("Random", "rd")
{
	
}


/**
 * Destroy random driver
 */
RandomDriver::~RandomDriver()
{	

}



/**
 * Probe the driver
 */
bool 
RandomDriver::Probe() 
{ 
	return true;
}




uint64_t 
RandomDriver::Write(uint8_t *data, uint64_t size, uint64_t offset)
{
	return 0;
}



uint64_t 
RandomDriver::Read(uint8_t *data, uint64_t size, uint64_t offset)
{
	unsigned int i;

	for(i = 0; i < size; i++)
	{
		data[i] = *((char *) data[i]) * i / arch_get_tick();
	}

	return 0;
}
