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
#include "Rs232.hpp"
#include <Driver.hpp>
#include <arch.h>


/**
 * Create the rs232 driver
 */
Rs232Driver::Rs232Driver() : Driver("Rs232", "rs")
{
	
}


/**
 * Destroy rs232 driver
 */
Rs232Driver::~Rs232Driver()
{
	unsetHandler(IRQ13);
	unsetHandler(IRQ24);
}




Rs232Driver::PortBuffer m_Buffers[4];


static void 
Rs232Callback(regs_t *reg)
{	
	if((io_inb(Rs232Driver::COM1 + 5) & 1) != 0)
	{
		m_Buffers[0].Data[m_Buffers[0].Point] = io_inb(Rs232Driver::COM1);
		m_Buffers[0].Size++;
		m_Buffers[0].Point++;
	}	
	if((io_inb(Rs232Driver::COM2 + 5) & 1) != 0)
	{
		m_Buffers[1].Data[m_Buffers[1].Point] = io_inb(Rs232Driver::COM2);
		m_Buffers[1].Size++;
		m_Buffers[1].Point++;
	}		
	if((io_inb(Rs232Driver::COM3 + 5) & 1) != 0)
	{
		m_Buffers[2].Data[m_Buffers[2].Point] = io_inb(Rs232Driver::COM3);
		m_Buffers[2].Size++;
		m_Buffers[2].Point++;
	}		
	if((io_inb(Rs232Driver::COM4 + 5) & 1) != 0)
	{
		m_Buffers[3].Data[m_Buffers[3].Point] = io_inb(Rs232Driver::COM4);
		m_Buffers[3].Size++;
		m_Buffers[3].Point++;
	}	
}


/**
 * Probe the driver
 */
bool 
Rs232Driver::Probe() 
{ 

	int x;
	
	initPort(Rs232Driver::COM1);
	initPort(Rs232Driver::COM2);
	initPort(Rs232Driver::COM3);
	initPort(Rs232Driver::COM4);
	
	for(x = 0; x < 4; x++)
		m_Buffers[x].Where = m_Buffers[x].Size = m_Buffers[x].Point = 0;
		
	setHandler(Rs232Driver::IRQ13, &Rs232Callback); 
	setHandler(Rs232Driver::IRQ24, &Rs232Callback);
	
	return true;
}



void 
Rs232Driver::initPort(uint32_t port)
{
	io_outb(port + 1, 0x01);    // Disable all interrupts
	io_outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	io_outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	io_outb(port + 1, 0x00);    //                  (hi byte)
	io_outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
	io_outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	io_outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}



uint64_t 
Rs232Driver::Read(uint8_t *data, uint64_t size, uint64_t offset)
{
	uint32_t i;
	
	for(i = 0; i < size; i++)
	{	
		m_Buffers[0].Data[i] = Receive(0);
	}	
	
	return i;
}


uint64_t
Rs232Driver::Write(uint8_t *data, uint64_t size, uint64_t offset)
{ 
	uint32_t i;
	
	for(i = 0; i < size; i++)
	{	
		Send(0, m_Buffers[0].Data[i]);
	}	
	
	return i; 
}






void 
Rs232Driver::Send(uint32_t port, uint8_t data)
{
	while ((io_inb(port + 5) & 0x20) == 0);
	io_outb(port, data);
}



uint8_t 
Rs232Driver::Receive(uint32_t port)
{
	char ch = 0;
	switch(port)
	{
		case Rs232Driver::COM1:
			if(m_Buffers[0].Size > 0)
			{
				ch = m_Buffers[0].Data[m_Buffers[0].Where];
				//putchar(ch);
				m_Buffers[0].Where++;
				m_Buffers[0].Size--;
			}
			return ch;
					
		case Rs232Driver::COM2:
			if(m_Buffers[1].Size > 0)
			{
				ch = m_Buffers[1].Data[m_Buffers[1].Where];
				m_Buffers[1].Where++;
				m_Buffers[1].Size--;
			}
			return ch;
			
		case Rs232Driver::COM3:
			if(m_Buffers[2].Size > 0)
			{
				ch = m_Buffers[2].Data[m_Buffers[2].Where];
				m_Buffers[2].Where++;
				m_Buffers[2].Size--;
			}
			return ch;
			
		case Rs232Driver::COM4:
			if(m_Buffers[3].Size > 0)
			{
				ch = m_Buffers[3].Data[m_Buffers[3].Where];
				m_Buffers[3].Where++;
				m_Buffers[3].Size--;
			}
			return ch;
	}
	return 0;
}

