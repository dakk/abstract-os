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
#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <iostream.hpp>
#include <ctype.h>
#include <arch.h>
#include <config.h>

/**
 * Generic driver clas
 */
class Driver
{
	public:
		Driver(char *name, char *devname);
		~Driver();
		virtual bool Probe() = 0;
		//static void Callback(void *);
		
		void Puts(char *msg);
		Driver *Next;
		char *getName();
		char *getDevName();

		void setHandler(uint8_t irq, void (*)(regs_t *));
		void unsetHandler(uint8_t irq);

		virtual uint64_t Read(uint8_t *data, uint64_t size, uint64_t offset) = 0;
		virtual uint64_t Write(uint8_t *data, uint64_t size, uint64_t offset) = 0;
		
	private:
		char m_Name[128];
		char m_DevName[128];
};

#endif
