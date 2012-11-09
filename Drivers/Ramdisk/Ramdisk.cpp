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
#include "Ramdisk.hpp"
#include <Driver.hpp>
#include <stdio.h>


extern multiboot_info_t *multiboot;


/**
 * Ramdisk constructor
 */
RamdiskDriver::RamdiskDriver() : Driver("Ramdisk", "ram")
{
	// do nothing
}



/**
 * Delete ramdisk instance
 */
RamdiskDriver::~RamdiskDriver()
{
	// do nothing
}



/**
 * Probe the ramdisk and assign address and size
 */
bool 
RamdiskDriver::Probe() 
{
	m_Address = (uint8_t *) (((multiboot_module_t *) multiboot->mods_addr)->mod_start);
	m_Size = (uint64_t) (((multiboot_module_t *) multiboot->mods_addr)->mod_end - (uint32_t) m_Address);
	
	//Puts("found ramdisk module");

	if(multiboot->mods_count != 0)
		return true;
	else
		return false;
}




/**
 * Read data from ramdisk
 */
uint64_t 
RamdiskDriver::Read(uint8_t *data, uint64_t size, uint64_t offset)
{
	unsigned i;

	if(offset > m_Size)
		return 0;

	for(i = 0; i < size; i++)
	{
		data[i] = m_Address[offset+i];

		if((i+offset) == (m_Size - 1))
			break;
	}
	return i;
}




/**
 * You can also write in the ramdisk, but you can't add data
 */
uint64_t 
RamdiskDriver::Write(uint8_t *data, uint64_t size, uint64_t offset)
{
	unsigned i;

	if(offset > m_Size)
		return 0;

	for(i = 0; i < size; i++)
	{
		m_Address[offset+i] = data[i];

		if((i+offset) == (m_Size - 1))
			break;
	}
	return i;
}


uint64_t RamdiskDriver::getSize()
{
	return m_Size;
}

