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
#include <types.h>
#include <arch.h>

#define IRQ_KEYBOARD	1
#define	SHIFT_LEFT		0x2A
#define	SHIFT_RIGHT		0x36
#define PAGE_UP			0x49
#define PAGE_DOWN		0x51
#define LOCK_CAPS		0x3A
#define LOCK_NUM		0x45
#define LED_NUM			2
#define LED_CAPS		4

unsigned shift;
unsigned alt;
unsigned control;
unsigned capslock;
unsigned numlock;

char buf[256];
uint8_t bufsize = 0;
int16_t bufpoint = -1;

///< Caratteri ascii
char keyboard_standard_charset[] = {
		0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', 0, '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',   
		0, 0, '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, 0, 0, 0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 
		'-', 0, 0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'-', 0, '5', 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
	};
			
///< Caratteri ascii maiuscoli
char keyboard_standard_charset_shifted[] = {
		0, 0, '!', '"', 0, '$', '%', '&', '/', '(', ')', '=', '?', '^', 0, '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[',
		']', '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '@', '#', 0, 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0,
		0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'-', 0, '5', 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
	};

uint16_t 
arch_kgetch()
{
	bufpoint--;
	
	if(bufsize <= 0)
		return 0;
		
	uint16_t ch = buf[bufpoint];
	bufpoint--;
	bufsize--;
	return ch;
}


void 
kkeyb_update_leds(uint8_t status)
{
 	while((io_inb(0x64)&2)!=0){}
 	io_outb(0x60,0xED);
 
 	while((io_inb(0x64)&2)!=0){}
 	io_outb(0x60,status);
}


void 
kkeyb_callback(regs_t *reg)
{	
	unsigned code = io_inb(0x60);
	
	// Tasto rilasciato
    if (code & 0x80)
    {
		code &= 0x7F;
		switch(code)
		{
			case SHIFT_LEFT:
			case SHIFT_RIGHT:
				shift = 0;
				break;
		}
    }
    // Tasto premuto
    else
    {
		switch(code)
		{						
			case LOCK_CAPS:
				capslock = !capslock;
				kkeyb_update_leds(LED_CAPS | LED_NUM);
				break;
				
			case LOCK_NUM:
				numlock = !numlock;
				kkeyb_update_leds(LED_CAPS | LED_NUM);
				break;
				
			case SHIFT_LEFT:
			case SHIFT_RIGHT:
				shift = 1;
				break;
			
			default:
				if((shift && !capslock) || (!shift && capslock)) buf[bufpoint] = keyboard_standard_charset_shifted[code];
				else buf[bufpoint] = keyboard_standard_charset[code];
				bufsize++;
				bufpoint++;
				break;
		}
    }
}


