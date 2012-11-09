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
#include <arch.h>
#include <types.h>

#define SERIAL_BASE 0x16000000
#define SERIAL_FLAG_REGISTER 0x18
#define SERIAL_BUFFER_FULL (1 << 5)


/* how? */
void 
arch_ksetcl(uint16_t cl)
{
}


/* clear */
void 
arch_kclear()
{
	int i;
	for(i = 0; i < 25; i++)
		arch_kputch('\n', -1, -1);
}


/* get a char from serial */
uint16_t 
arch_kgetch()
{
    while (*(volatile unsigned long*)(SERIAL_BASE + SERIAL_FLAG_REGISTER) 
                                       & (SERIAL_BUFFER_FULL));

    return (char) (*(volatile unsigned long*) SERIAL_BASE);
}


/* put a char in serial */
void 
arch_kputch(uint8_t ch, int16_t x, int16_t y)
{
    while (*(volatile unsigned long*)(SERIAL_BASE + SERIAL_FLAG_REGISTER) 
                                       & (SERIAL_BUFFER_FULL));

    *(volatile unsigned long*)SERIAL_BASE = ch;
}
