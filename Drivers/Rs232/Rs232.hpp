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
#ifndef RS232_HPP
#define RS232_HPP

#include <malloc.h>
#include <types.h>
#include <string.h>
#include <config.h>

#include <Driver.hpp>



/**
 * Rs232 serial driver
 */
class Rs232Driver : public Driver
{
	public:
		static const unsigned IRQ24	= 3;
		static const unsigned IRQ13	= 4;

		static const unsigned COM1 = 0x3f8;
		static const unsigned COM2 = 0x2f8;
		static const unsigned COM3 = 0x3e8;
		static const unsigned COM4 = 0x2e8;

		Rs232Driver();
		~Rs232Driver();
		
		bool Probe();

		uint64_t Read(uint8_t *data, uint64_t size, uint64_t offset);
		uint64_t Write(uint8_t *data, uint64_t size, uint64_t offset);
		void Send(uint32_t port, uint8_t data);
		uint8_t Receive(uint32_t port);

		typedef struct
		{
			char Data[256];
			uint8_t Size;
			uint8_t Where;
			uint8_t Point;	
		} PortBuffer;

		void initPort(uint32_t port);

};


#endif
