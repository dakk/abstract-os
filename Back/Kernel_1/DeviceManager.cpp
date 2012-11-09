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
#include <DeviceManager.hpp>
#include <types.h>
#include <Device.hpp>
#include <Driver.hpp>
#include <Managers.hpp>
#include <string.h>



DeviceManager::DeviceManager()
{
	m_DeviceList = new list<Device>();
}


DeviceManager::~DeviceManager()
{
	delete m_DeviceList;
}


/**
 * Get a Device by the id
 */
Device *
DeviceManager::getDevice(unsigned i)
{
	return m_DeviceList->getNode(i);
}



/**
 * Get a Device by the name
 */
Device *
DeviceManager::getDevice(char *name)
{
	return m_DeviceList->getNodeByName(name);	
}



/**
 * Add a driver
 * 
 * \return state of the operation
 */
bool
DeviceManager::addDevice(Device *device)
{
	if(device->getName()[0] == 0)
		return false;
		
	return m_DeviceList->addNode(device);
}



/**
 * Probe all plugged devices
 * 
 * \return number of devices recognized
 */
int
DeviceManager::Probe(BusType type)
{
	int n = 0;

	m_DeviceList->Clear();

	Driver *drv = Managers::Instance->driverManager->getDriver((unsigned) 0);

	while(drv != NULL)
	{
		if((drv != NULL) && (drv->Probe()))
		{
			n++;
			
			char dev_name[128];
			strcpy(dev_name, drv->getDevName());
			strcat(dev_name, "0\0");

			Device *dev = new Device(dev_name, drv);
			addDevice(dev);

			/* init the device? */

			cout<<dev->getName();
			cout<<" ";
		}

		drv = drv->Next;
	}

	return n;
}



unsigned
DeviceManager::getDevicesNumber()
{
	return m_DeviceList->Len;
}
