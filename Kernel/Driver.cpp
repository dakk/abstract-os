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
#include <Driver.hpp>
#include <string.h>
#include <stdio.h>

/**
 * Create a driver
 */
Driver::Driver(char *name, char *devname)
{
	strcpy(m_Name, name);
	strcpy(m_DevName, devname);
}


/**
 * Destroy a driver
 */
Driver::~Driver()
{
	
}


void 
Driver::setHandler(uint8_t irq, void (*f)(regs_t *))
{
	#ifdef X86
		handler_reg(irq, f);
	#endif
}



void 
Driver::unsetHandler(uint8_t irq)
{
	#ifdef X86
		handler_unreg(irq);
	#endif
}


/**
 * Display a message
 */
void 
Driver::Puts(char *msg)
{
	printf("%s: %s\n", m_Name, msg);
}


/**
 * Get the driver name
 */
char *
Driver::getName()
{
	return m_Name;
}

/*

bool
Driver::Probe()
{
	return true;
}*/


char * 
Driver::getDevName()
{
	return m_DevName;
}
