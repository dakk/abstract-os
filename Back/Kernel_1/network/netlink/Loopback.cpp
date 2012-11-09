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
#include <network/netlink/Loopback.hpp>

int 
NetlinkLoopback::handlePacket(NetworkIface *iface, Packet *p)
{
	uint16_t protocol;
	unsigned i;
	

	Header *lohead = (Header *) p->Data;
	protocol = lohead->protocol;
	p->delHeader(sizeof(Header));

	
	i = iface->NetProto->handlePacket(iface, p);

	iface->RxBytes += i;

	return i;
}



int 
NetlinkLoopback::sendPacket(NetworkIface *iface, Packet *p)
{
	handlePacket(iface, p);
	
	iface->TxBytes += p->Size;

	return p->Size;	
}

