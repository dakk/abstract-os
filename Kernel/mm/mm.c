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
#include <mm/mm.h>
#include <mm/phys.h>
#include <mm/paging.h>
#include <config.h>



/** Initialize memory manager */
int
mm_init(uint64_t mem)
{
	phys_init(mem);

	#ifdef PAGING
		//paging_init();
	#endif
	
	return 0;
}



/** Alloc a block */
void *
mm_alloc(size_t size)
{	
	unsigned bnum = (unsigned) ((size + 1) / (PHYS_PAGE_SIZE * 1024)) + 1; 
	// / PHYS_PAGE_SIZE + 1;
	return (void *)phys_alloc(bnum);
}


/** Free a block */
void 
mm_free(void *addr)
{
	phys_free(addr);
}


/** Return total memory */
uint32_t 
mm_get_total_mem()
{ 
	return phys_total;
}


/** Return used memory */
uint32_t 
mm_get_used_mem()
{ 
	return ((phys_page_number - phys_get_free_pages()) * PHYS_PAGE_SIZE);
}



/** Get allocation size */
uint32_t 
mm_get_usable_size(void *addr)
{
	int i = 0;

	for(i = 0; i < PHYS_MAX_BLOCKS; i++)
		if(phys_allocated[i].address == addr)
			return phys_allocated[i].dim;
	
	return 0;
}

