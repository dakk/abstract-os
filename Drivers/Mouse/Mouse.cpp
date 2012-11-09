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
#include "Mouse.hpp"
#include <types.h>
#include <Driver.hpp>
#include <stdio.h>



unsigned Cycle;
char Byte[3];



bool 
MouseDriver::Probe()
{
	return true;	
}


void 
Wait(uint8_t a_type)
{
	uint32_t time_out = 100000;
	
	if(a_type == 0)
	{
		while(time_out--)
			if((io_inb(0x64) & 1) == 1) return;
		
		return;
	}
	else
	{
		while(time_out--)
		  if((io_inb(0x64) & 2) == 0) return;
		return;
	}
}


void 
MouseWrite(uint8_t a_write)
{
	Wait(1);
	io_outb(0x64, 0xD4);
	Wait(1);
	io_outb(0x60, a_write);
}


uint8_t 
MouseRead()
{
	Wait(0); 
	return io_inb(0x60);
}



static void 
MouseCallback(regs_t *reg)
{	
	switch(Cycle)
	{
		case 0:
			Byte[0] = io_inb(0x60);
			Cycle++;
			break;
			
		case 1:
			Byte[1] = io_inw(0x60);
			Cycle++;
			break;
			
		case 2:
			Byte[2] = io_inw(0x60);
			Cycle = 0;
			//printf("%d %d\n",  Byte[1], Byte[2]);
			break;
	}	
}


MouseDriver::MouseDriver() : Driver("Mouse", "ps")
{
	uint8_t status;
	
	Wait(1);
	io_outb(0x64, 0xA8);
  
	Wait(1);
	io_outb(0x64, 0x20);
	Wait(0);
	status = (io_inb(0x60) | 2);
	Wait(1);
	io_outb(0x64, 0x60);
	Wait(1);
	io_outb(0x60, status);
  
	// Valori di default
	MouseWrite(0xF6);
	MouseRead();

	// Abilita lo sacmbio dati
	MouseWrite(0xF4);
	MouseRead();
	
	// Scaling 1:1
	MouseWrite(0xE6);
	MouseRead();
	
	// Imposta l'handler
	setHandler(MouseDriver::IRQ, &MouseCallback);
}


int
MouseDriver::getX()
{	
	MouseDriver::Packet *p = (MouseDriver::Packet *) &Byte[0];

	if(p->x_sign_bit)
		return Byte[1];
	else
		return -Byte[1];
	return 0;
}



int
MouseDriver::getY()
{	
	MouseDriver::Packet *p = (MouseDriver::Packet *) &Byte[0];

	if(p->y_sign_bit)
		return Byte[2];
	else
		return -Byte[2];
	return 0;
}



bool 
MouseDriver::getClickedRt()
{
	MouseDriver::Packet *p = (MouseDriver::Packet *) &Byte[0];

	return (bool) (p->right_btn);
}



bool 
MouseDriver::getClickedMd()
{
	MouseDriver::Packet *p = (MouseDriver::Packet *) &Byte[0];

	return (bool) (p->middle_btn);
}



bool 
MouseDriver::getClickedLt()
{
	MouseDriver::Packet *p = (MouseDriver::Packet *) &Byte[0];

	return (bool) (p->left_btn);
}

