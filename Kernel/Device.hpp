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
#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <Driver.hpp>
#include <iostream.hpp>



/** \addtogroup devdrv
 * @{
 */



/** Enumeration for the bus type */
typedef enum { EBT_PCI, EBT_ISA, EBT_USB } BusType;




/**
 * Device class
 */
class Device
{
	public:
					Device(char *name, Driver *driver, BusType bt = EBT_PCI);
					~Device();
			
		char *		getName();
		Driver *	getDriver();
		char *		getClass();
		char *		getSubClass();
		
		Device *	Next;
		
	private:
		char 		m_Name[128];			///< Name of the device (like hd0, eth0)
		char 		m_Class[128];			///< Class
		char 		m_SubClass[128];		///< Sub class
		Driver *	m_Driver;				///< Driver of the device
		BusType 	m_BusType;				///< Type of the bus used
	
};



/** @} */

#endif
