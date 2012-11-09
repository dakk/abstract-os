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
#include <DriverManager.hpp>
#include <Driver.hpp>
#include <types.h>
#include <config.h>
#include <iostream.hpp>
#include <list.hpp>
#include <Driver.hpp>
#include <Drivers/Vesa/Vesa.hpp>
#include <Drivers/Mouse/Mouse.hpp>
#include <Drivers/Framebuffer/Framebuffer.hpp>
#include <Drivers/Ramdisk/Ramdisk.hpp>
#include <Managers.hpp>
#include <Drivers/Pcspk/Pcspk.hpp>
#include <Drivers/Rs232/Rs232.hpp>
#include <Drivers/Smbios/Smbios.hpp>
#include <Drivers/Random/Random.hpp>
#include <Drivers/Rtl8139/Rtl8139.hpp>
#include <Drivers/Keyboard/Keyboard.hpp>


/**
 * Create the driver manager
 *
 * \todo add in the build script, a function to create an automatic list of the
 * 		constructors
 */
DriverManager::DriverManager()
{
	m_DriverList = new list<Driver>();
	
	#ifdef VESA
		addDriver(new VesaDriver());
	#endif	
	#ifdef MOUSE
		addDriver(new MouseDriver());
	#endif	
	#ifdef FRAMEBUFFER
		addDriver(new FramebufferDriver());
	#endif	
	#ifdef RAMDISK
		addDriver(new RamdiskDriver());
	#endif
	#ifdef RS232
		addDriver(new Rs232Driver());
	#endif
	#ifdef PCSPK
		addDriver(new PcspkDriver());
	#endif
	#ifdef SMBIOS
		addDriver(new SmbiosDriver());
	#endif
	#ifdef RANDOM
		addDriver(new RandomDriver());
	#endif
	#ifdef RTL8139
		addDriver(new Rtl8139Driver());
	#endif
	#ifdef KEYBOARD
		addDriver(new KeyboardDriver());
	#endif
}


/**
 * Destroy the driver manager
 */
DriverManager::~DriverManager()
{
	/* delete all drivers */
	delete m_DriverList;
}



/**
 * Add a driver
 * 
 * \return state of the operation
 */
bool
DriverManager::addDriver(Driver *driver)
{
	if(driver->getName()[0] == 0)
		return false;
		
	return m_DriverList->addNode(driver);
}



/**
 * Add a driver from file
 * 
 * \return state of the operation
 */
bool 
DriverManager::addDriver(char *driver_path)
{
	return false;	
}



/**
 * Get a driver by the id
 */
Driver *
DriverManager::getDriver(unsigned i)
{
	return (Driver *) m_DriverList->getNode(i);
}



/**
 * Get a driver by the name
 */
Driver *
DriverManager::getDriver(char *name)
{
	return (Driver *) m_DriverList->getNodeByName(name);	
}



/**
 * Delete a driver by the name
 */
void 
DriverManager::delDriver(char *name)
{
	m_DriverList->delNodeByName(name);
}



/**
 * Delete a driver by the id
 */
void 
DriverManager::delDriver(unsigned i)
{
	m_DriverList->delNode(i);
}

