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
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <types.h>
#include <Driver.hpp>
#include <arch.h>


class MouseDriver : public Driver
{
	public:
		static const unsigned IRQ	= 12;


		typedef struct
		{
			uint8_t y_overflow:1;
			uint8_t x_overflow:1;
			uint8_t y_sign_bit:1;
			uint8_t x_sign_bit:1;
			uint8_t alw_1:1;
			uint8_t middle_btn:1;
			uint8_t right_btn:1;
			uint8_t left_btn:1;
		} Packet;

		MouseDriver();
		~MouseDriver();
		
		bool Probe();

		
		uint64_t Read(uint8_t *data, uint64_t size, uint64_t offset){ return 0; };
		uint64_t Write(uint8_t *data, uint64_t size, uint64_t offset){ return 0; };


		bool getClickedRt();
		bool getClickedLt();
		bool getClickedMd();
		int getX();
		int getY();

};

#endif
