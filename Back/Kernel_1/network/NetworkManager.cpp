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
#include <network/NetworkManager.hpp>
#include <network/netlink/Loopback.hpp>
#include <network/netproto/Ipv4.hpp>


/** Create network manager */
NetworkManager::NetworkManager()
{
	m_IfaceList = new list<NetworkIface>();
}


/** Destroy network manager */
NetworkManager::~NetworkManager()
{
	delete m_IfaceList;
}


/** 
 * Probe and add all network ifaces 
 *
 * \return number of probed interfaces
 */
int
NetworkManager::Probe()
{
	return 0;
}


/** Return the i iface */
NetworkIface *
NetworkManager::getIface(unsigned i)
{
	return m_IfaceList->getNode(i);
}



/** Return the iface with the argument name */
NetworkIface *
NetworkManager::getIface(char *name)
{
	return m_IfaceList->getNodeByName(name);
}
