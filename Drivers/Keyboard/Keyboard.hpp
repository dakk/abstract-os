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
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <types.h>
#include <Driver.hpp>
#include <arch.h>


class KeyboardDriver : public Driver
{
	public:
		typedef struct
		{
			bool LShift;
			bool RShift;
			bool Alt;
			bool Control;
			bool CapsLock;
			bool NumLock;

			unsigned Code;
		} Stat;

		static const unsigned 	IRQ	= 1;

		static const uint8_t SHIFT_LEFT		=	0x2A;
		static const uint8_t SHIFT_RIGHT	=	0x36;
		static const uint8_t PAGE_UP		=	0x49;
		static const uint8_t PAGE_DOWN		=	0x51;
		static const uint8_t LOCK_CAPS		=	0x3A;
		static const uint8_t LOCK_NUM		=	0x45;
		static const uint8_t LED_NUM		=	2;
		static const uint8_t LED_CAPS		=	4;

		KeyboardDriver();
		~KeyboardDriver();
		
		bool Probe();

		Stat getKeysState();

		
		uint64_t Read(uint8_t *data, uint64_t size, uint64_t offset);
		uint64_t Write(uint8_t *data, uint64_t size, uint64_t offset){ return 0; };
};

#endif
