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
 
		
extern "C"
{
	int ElfExec(unsigned off, unsigned data, int argc, char **argv)
	{
		void (*f)();
		f = (void (*)()) ((void *) ((uint32_t) data + (uint32_t) off));
		f();
		return 0;
	}
}


/* Exec the binary elf program */
int 
Elf::Exec(int argc, char **argv)
{
	Header *h = (Header *) m_Data;
	/*int (*f)(int argc, char **argv) = h->phoff;
	
	return f(argc, argv);*/
//		void (*f)();
//		f = (void *) ((uint32_t) m_Data + (uint32_t) h->phoff);
	ElfExec(h->phoff, (unsigned) m_Data, argc, argv);

	return 0;
}

		
/** Check if the data is elf data */
bool
Elf::Check()
{
	Header *header = (Header *) m_Data;
		
	if( (*(header->ident+1) == 'E') &&
		(*(header->ident+2) == 'L') &&
		(*(header->ident+3) == 'F') &&
		(*(header->ident) == 0x7f))
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
