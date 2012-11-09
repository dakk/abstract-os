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

#include "archinc.h"
#include "dt.h"
#include <arch.h>
#include <types.h>
#include <kernel.h>
#include <klibc/typeconv.h>
#include <klibc/stdio.h>


/* clock callback */
static void 
clock_callback(regs_t *r)
{
	io_outb(RTCaddress,0x04);
	clock_data.hours = 	(uint8_t) bcd2bin(io_inb(RTCdata));

	io_outb(RTCaddress,0x02);
	clock_data.minutes = (uint8_t) bcd2bin(io_inb(RTCdata));
	
	io_outb(RTCaddress,0);
	clock_data.seconds = (uint8_t) bcd2bin(io_inb(RTCdata));

	io_outb(RTCaddress,0x08);	
	clock_data.month = (uint8_t) bcd2bin(io_inb(RTCdata));
	
	io_outb(RTCaddress,0x09);
	clock_data.year = (uint8_t) bcd2bin(io_inb(RTCdata));

	io_outb(RTCaddress,0x07);	
	clock_data.day = (uint8_t) bcd2bin(io_inb(RTCdata));
	
	//printf("%d %d %d\n", clock_data.hours, clock_data.minutes, clock_data.seconds);
}


/* rtc init */
void 
clock_init()
{
	char prev;
	
	io_outb(0x70, 0x0B); 
	prev = io_inb(0x71); 
	io_outb(0x70, 0x0B); 
	io_outb(0x71, prev | 0x40);

	handler_reg(8, &clock_callback);
}



/* utc clock */
uint32_t 
arch_get_clock()
{
	return 0;
}
