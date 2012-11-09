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
#ifndef MANAGERS_HPP
#define MANAGERS_HPP

#include <config.h>
#include <Driver.hpp>
#include <DriverManager.hpp>
#include <Device.hpp>
#include <DeviceManager.hpp>
#include <iostream.hpp>
#include <TaskManager.hpp>
#include <bus/pci/PciBus.hpp>
#include <vfs/VFSManager.hpp>
#include <ui/UiManager.hpp>
#include <network/NetworkManager.hpp>
#include <ArchManager.hpp>
#include <print/PrintManager.hpp>
#include <media/MediaManager.hpp>
#include <security/SecurityManager.hpp>



class Managers
{		 
	public:
		static Managers *		Instance;
		
		DeviceManager *			deviceManager;
		DriverManager *			driverManager;	
		TaskManager *			taskManager;
		ArchManager *			archManager;
		
		VFSManager *			vfsManager;
		NetworkManager *		netManager;
		PciBus *				pciBus;
		UiManager *				uiManager;
		PrintManager *			printManager;
		SecurityManager *		securityManager;
		MediaManager *			mediaManager;

		~Managers()
		{
		
		}

		Managers()
		{
		
		}
};




#endif
