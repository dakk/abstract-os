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
#include <network/Packet.hpp>

/** Create a packet */
Packet::Packet(uint32_t size, char *data)
{
	Size = size;

	Data = (char *) malloc(size);
	if(data != NULL)
		memcpy(Data, data, size);
}


/** Destroy the packet */
Packet::~Packet()
{
	free(Data);
}



/** Add an header section */
void  
Packet::addHeader(uint32_t size, char *head)
{
	char *data = (char *) malloc(Size + size);
	memcpy(data + size, Data, Size);
	memcpy(data, head, size);
	free(Data);
	Data = data; 
	Size += size;	
}


/** Delete an header section */
void 
Packet::delHeader(uint32_t size)
{
	char *data = (char *) malloc(Size - size);
	memcpy(data, Data + size, Size - size);
	free(Data);
	Data = data;
	Size -= size;
}



/** Calculate the packet chesum */
uint32_t
Packet::Checksum32()
{
	unsigned i;
	uint32_t checksum = 0;

	for(i = 0; i < Size; i++)
		checksum += Data[i];

	return checksum;
}

