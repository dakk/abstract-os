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
#ifndef NETWORKIFACE_HPP
#define NETWORKIFACE_HPP

#include <ctype.h>
#include <Device.hpp>
#include "Packet.hpp"


class NetworkIface;

/** Eth, lo, ppp */
class NetlinkProto
{
	public:
		virtual int handlePacket(NetworkIface *iface, Packet *p) = 0;
		virtual int sendPacket(NetworkIface *iface, Packet *p) = 0;
};


/** Ip, icmp... To define */
class NetworkProto
{
	public:
		virtual int handlePacket(NetworkIface *iface, Packet *p) = 0;
};


/** A network interface */
class NetworkIface
{
	public:
		NetworkIface(char *name, Device *dev, NetlinkProto *netlink, NetworkProto *netproto);
		~NetworkIface();
		char *getName();

		NetworkIface *Next;						///< Next interface

		char *Address;
		uint64_t RxBytes;						///< Rx bytes
		uint64_t TxBytes;						///< Tx bytes
		bool Enabled;							///< True if the iface is enabled
		
		NetlinkProto *LinkProto;				///< Netlink protocol
		NetworkProto *NetProto;				///< Network protocol



	private:
		char m_Name[128];						///< Interface name};
};


#endif
