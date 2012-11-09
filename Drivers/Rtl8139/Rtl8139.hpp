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
#ifndef RTL8139_HPP
#define RTL8139_HPP

#include <klibc/malloc.h>
#include <types.h>
#include <string.h>
#include <config.h>
#include <Driver.hpp>
#include <bus/pci/PciBus.hpp>


/**
 * Rtl8139 network driver
 */
class Rtl8139Driver : public Driver
{
	public:
		typedef enum
		{
			MAC0	= 0x00,
			MAR0	= 0x08,
			RBSTART = 0x30,
			CMD		= 0x37,
			IMR		= 0x3C,
			ISR		= 0x3E
		} RegisterOffsets;

		static const PciBus::Entry PciList[];
		static const unsigned PciListSize = 18;


		Rtl8139Driver();
		~Rtl8139Driver();
		
		bool Probe();

		uint64_t Read(uint8_t *data, uint64_t size, uint64_t offset){ return 0; };
		uint64_t Write(uint8_t *data, uint64_t size, uint64_t offset){ return 0; };
};


#endif
