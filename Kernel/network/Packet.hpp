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
#ifndef PACKET_HPP
#define PACKET_HPP

#include <ctype.h>
#include <malloc.h>
#include <string.h>


/** \addtogroup net
 * @{
 */

/** Network packet
 * \note last level in the network stack, should delete the packet
 */
class Packet
{
	public:
					Packet(uint32_t size, char *data = NULL);
					~Packet();

		void		delHeader(uint32_t size);
		void		addHeader(uint32_t size, char *data = NULL);

		uint32_t	Checksum32();

		char *		Data;						///< Packet data
		uint32_t	Size;						///< Packet size
};


/** @} */


#endif
