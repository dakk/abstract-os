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
#include "Keyboard.hpp"
#include <types.h>
#include <Driver.hpp>
#include <stdio.h>


bool KeyTake = true;
KeyboardDriver::Stat Keys;


///< Caratteri ascii
char standardCharset[] = {
		0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', 0, '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',   
		0, 0, '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, 0, 0, 0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 
		'-', 0, 0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'-', 0, '5', 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
	};
			
///< Caratteri ascii maiuscoli
char standardCharsetShifted[] = {
		0, 0, '!', '"', 0, '$', '%', '&', '/', '(', ')', '=', '?', '^', 0, '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[',
		']', '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '@', '#', 0, 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0,
		0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'-', 0, '5', 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
	};


bool 
KeyboardDriver::Probe()
{
	return true;	
}


void 
updateLeds(uint8_t status)
{
 	while((io_inb(0x64)&2)!=0){}
 	io_outb(0x60,0xED);
 
 	while((io_inb(0x64)&2)!=0){}
 	io_outb(0x60,status);
}

static void 
KeyboardCallback(regs_t *reg)
{	
	unsigned code = io_inb(0x60);

	// Tasto rilasciato
    if (code & 0x80)
    {
		code &= 0x7F;
		switch(code)
		{
			case KeyboardDriver::SHIFT_LEFT:
				Keys.LShift = false;
				break;

			case KeyboardDriver::SHIFT_RIGHT:
				Keys.RShift = false;
				break;
		}
    }
    // Tasto premuto
    else
    {
		switch(code)
		{						
			case KeyboardDriver::LOCK_CAPS:
				Keys.CapsLock = !Keys.CapsLock;
				updateLeds(KeyboardDriver::LED_CAPS | KeyboardDriver::LED_NUM);
				break;
				
			case KeyboardDriver::LOCK_NUM:
				Keys.NumLock = !Keys.NumLock;
				updateLeds(KeyboardDriver::LED_CAPS | KeyboardDriver::LED_NUM);
				break;
				
			case KeyboardDriver::SHIFT_LEFT:
				Keys.LShift = true;
				break;

			case KeyboardDriver::SHIFT_RIGHT:
				Keys.RShift = true;
				break;
			
			default:
				Keys.Code = code;
				//if((shift && !capslock) || (!shift && capslock)) buf[bufpoint] = keyboard_standard_charset_shifted[code];
				//else buf[bufpoint] = keyboard_standard_charset[code];
				//bufsize++;
				//bufpoint++;
				break;
		}
    }

}


KeyboardDriver::KeyboardDriver() : Driver("Keyboard", "kb")
{
	Keys.RShift = false;
	Keys.LShift = false;
	Keys.Alt = false;
	Keys.Control = false;
	Keys.CapsLock = false;
	Keys.NumLock = false;
	Keys.Code = 0;

	// Imposta l'handler
	setHandler(KeyboardDriver::IRQ, &KeyboardCallback);
}



KeyboardDriver::Stat 
KeyboardDriver::getKeysState()
{
	return Keys;
}

 

uint64_t 
KeyboardDriver::Read(uint8_t *data, uint64_t size, uint64_t offset)
{ 
	*data = Keys.Code;
	return 1;
}
