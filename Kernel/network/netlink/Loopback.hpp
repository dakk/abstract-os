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
#ifndef LOOPBACK_HPP
#define LOOPBACK_Hpp

#include <network/NetworkIface.hpp>

/** \addtogroup net
 * @{
 */

class NetlinkLoopback
{
	public:
		typedef struct
		{
			uint16_t protocol;
		} Header;

		virtual int handlePacket(NetworkIface *iface, Packet *p);
		virtual int sendPacket(NetworkIface *iface, Packet *p);
};


/** @} */


#endif
