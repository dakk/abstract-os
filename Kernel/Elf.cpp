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
#include <Elf.hpp>
#include <stdio.h>


		
Elf::Elf(char *data, unsigned size)
{
	m_Data = data;
	m_Size = size;
}


Elf::~Elf()
{
	delete m_Data;
}
 


/** Relocate elf symbols; return number of relocated entry */
unsigned 
Elf::Relocate32()
{
	return 0;
}


/** Debug print of elf info */
void 
Elf::printInfo()
{
	Header *h = (Header *) m_Data;

	printf("\tMachine: ");
	switch(h->Machine)
	{
		case MAC_386:
			printf("386\n");
			break;
	}

	/*
	printf("\tClass: ");
	switch(h->Class)
	{
		case CLASS_32:
			printf("32 bit\n"); 
	}
	*/
}



/** Return elf entry point */
void *
Elf::getEntry()
{
	Header *h = (Header *) m_Data;
	return (void *) (m_Data + h->PhOff);
}



/** Exec the elf program \TODO DEPRECATED*/
int 
Elf::Exec(char **argv, char **env)
{
	void (*f)();
	f = (void(*)()) (getEntry());

	f();

	return 0;
}

		

/** Check if the data is elf data */
bool
Elf::Check()
{
	Header *header = (Header *) m_Data;
		
	if( (*(header->Ident+1) == 'E') &&
		(*(header->Ident+2) == 'L') &&
		(*(header->Ident+3) == 'F') &&
		(*(header->Ident) == 0x7f))
		return true;
	
	return false;		
}


/** Get the header */
Elf::Header *
Elf::getHeader()
{
	return (Header *) m_Data;
}



/** Return the i section entry header */
Elf::SectionHeader *
Elf::getSectionHeader(uint32_t i)
{
	return (SectionHeader *) NULL;
}
