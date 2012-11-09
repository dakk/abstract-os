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
#include "Smbios.hpp"
#include <Driver.hpp>


/**
 * Create the smbios driver
 */
SmbiosDriver::SmbiosDriver() : Driver("Smbios", "smb")
{
	
}


/**
 * Destroy smbios driver
 */
SmbiosDriver::~SmbiosDriver()
{
	
}



/**
 * Probe the driver
 */
bool 
SmbiosDriver::Probe() 
{
	char *mem = (char *) 0xF0000;
	uint32_t length, i;
	char checksum;
	
	while ((uint32_t) mem < 0x100000)
	{
		if(mem[0] == '_' && mem[1] == 'S' && mem[2] == 'M' && mem[3] == '_')
		{
			length = mem[5];
			checksum = 0;
			for(i = 0; i < length; i++)
				checksum += mem[i];
				
			if(checksum == 0)
			{
				m_Pointer = mem; 
				return true;
			}
		}
		mem += 16;
	}   
	return false;
}
