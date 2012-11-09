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

#include <klibc/ctype.h>
#include <klibc/malloc.h>
#include <klibc/string.h>
#include <mm/mm.h>

uint32_t allocazioni;


/* alloc and full with zeros */
void *
calloc(size_t size2, size_t size)
{
	int x;
	char *adr = (char *) mm_alloc(size);
	char *j = adr;

	for(x = 0; x < size; x++)
	{
		*j = 0;
		j++;
	}
	return (void *) adr;
}


/* alloc */
void *
malloc(size_t size)
{
	allocazioni++;

	return (void *) mm_alloc(size);
}


/* realloc */
void *
realloc(void *adr, size_t size)
{
	void *new = (void *) mm_alloc(size);
	memcpy(new, adr, size);
	//free(adr);

	return (void *) new;
}


/* free memory */
void 
free(void *adr)
{
	allocazioni--;
	
	mm_free(adr);
}
