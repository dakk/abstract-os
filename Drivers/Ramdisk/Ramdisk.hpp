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
 #ifndef RAMDISK_HPP
#define RAMDISK_HPP

extern "C"
{
	#include "Kernel/arch/x86/multiboot.h"
	#include <types.h>
	#include <config.h>
}	
#include <string.h>
#include <malloc.h>
#include <Driver.hpp>



/**
 * Ramdisk driver
 */
class RamdiskDriver : public Driver
{
	public:
		RamdiskDriver();
		~RamdiskDriver();
		
		bool Probe();
		uint64_t Read(uint8_t *data, uint64_t size, uint64_t offset);
		uint64_t Write(uint8_t *data, uint64_t size, uint64_t offset);

		uint64_t getSize();




	private:
		uint8_t *m_Address;
		uint64_t m_Size;
};


#endif
