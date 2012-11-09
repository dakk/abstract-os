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
#include "Pcspk.hpp"
#include <arch.h>
#include <Driver.hpp>


/**
 * Create the pcspk driver
 */
PcspkDriver::PcspkDriver() : Driver("Pcspk", "spk")
{
	
}


/**
 * Destroy pcspk driver
 */
PcspkDriver::~PcspkDriver()
{	
	uint8_t tmp = (io_inb(0x61) & 0xFC);
  	io_outb(0x61, tmp);
}



/**
 * Probe the driver
 */
bool 
PcspkDriver::Probe() 
{ 
	return true;
}




uint64_t 
PcspkDriver::Write(uint8_t *data, uint64_t size, uint64_t offset)
{
	uint32_t i;
	
	for(i = 0; i < size; i++)
	{	
		uint32_t div;
		uint8_t tmp;
	 
	 
		div = 1193180 / data[i];
		io_outb(0x43, 0xb6);
		io_outb(0x42, (uint8_t ) (div) );
		io_outb(0x42, (uint8_t ) (div >> 8));
	 
		tmp = io_inb(0x61);

		if (tmp != (tmp | 3))
			io_outb(0x61, tmp | 3);
	}	
	
	return i;
}



uint64_t 
PcspkDriver::Read(uint8_t *data, uint64_t size, uint64_t offset)
{
	return 0;
}
