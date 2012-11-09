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
#include <mm/phys.h>


/** Free physical blocks */
void 
phys_free(void *addr)
{
	unsigned x;
	unsigned y;
	unsigned i;
	unsigned j;
	
	// Dealloca dalla lista delle allocazioni e azzera la bitmap
	for(i = 0; i < PHYS_MAX_BLOCKS; i++)
		if(phys_allocated[i].address == addr)
		{
			// Azzera i bit della bitmap
			x = ((unsigned) addr / 4096) / 32;
			y = ((unsigned) addr / 4096) % 32;

			phys_bitmap[x] = phys_bitmap[x] - (1 << y);
	
			for(j = 1; j < phys_allocated[i].dim; j++)
			{
				if(y == 31)
				{
					y = 0;
					x++;
				}
				else
					y++;

				phys_bitmap[x] = phys_bitmap[x] - (1 << y);
			}

			// Libera l'elemento della lista
			phys_allocated[i].dim = 0;
		
			break;
		}	
}


/** Update x and y if the given page[x, y] is free */
uint8_t 
phys_if_free_page(int *x, int *y)
{
	if(*y == 31)
	{
		*y = 0;
		*x = *x + 1;
	}
	else
		*y = *y + 1;
	
	if((phys_bitmap[(int) *x] & (1 << (int) *y)) == 1)	
		return 0;
	else
		return 1;
}

/** Allocate a physical block */
void *
phys_alloc(size_t size)
{
	unsigned adr;
	unsigned x;
	unsigned y;
	unsigned j;
	int a,b;
	int ff;
	
	
	x = 0;
	while(x < (phys_page_number / 32))
	{
		y = 0;
		while(y < 32)
		{		
			if((phys_bitmap[x] & (1 << y)) == 0)
			{	
				a = x;
				b = y;
				for(j = 0; j <= size; j++)
				{
					if(j == size)
					{
						// Riempie la bitmap
						phys_bitmap[x] = phys_bitmap[x] + (1 << y);

						for(j = 1; j < size; j++)
						{
							if(y == 31)
							{
								y = 0;
								x++;
							}
							else
								y++;

							phys_bitmap[x] = phys_bitmap[x] + (1 << y);
						}

				
						adr = (x) * (1024 * 32 * PHYS_PAGE_SIZE) + (y * 1024 * PHYS_PAGE_SIZE);
						
						ff = phys_first_free_alloc();
						phys_allocated[ff].address = (void *) adr;
						phys_allocated[ff].dim = size;
						return (void *) adr;
					}
					if(!phys_if_free_page(&a, &b))
					{
						x = a;
						y = b;
						break;
					}
				}
			}
			y++;
		}
		x++;
	}

	// Non ci sono pagine disponibili
	return (void *) -1;
}



/** Return the number of used pages */
uint32_t 
phys_get_free_pages()
{
	unsigned np = 0;
	unsigned x;
	unsigned y;
	
	for(x = 0; x < phys_page_number / 32; x++)
	{
		for(y = 0; y < 32; y++)
			if((phys_bitmap[x] & (1 << y)) == 0)
				np++;
	}
	return np;	
}


/** Reserve a physical area */
void 
phys_reserve(uint32_t start, uint32_t end)
{
	unsigned x1, x2;
	unsigned y1, y2;
	
	// Azzera i bit della bitmap
	x1 = ((unsigned) start / 4096) / 32;
	y1 = ((unsigned) start / 4096) % 32;
	x2 = ((unsigned) end / 4096) / 32;
	y2 = ((unsigned) end / 4096) % 32;

	phys_bitmap[x1] = phys_bitmap[x1] - (1 << y1);
	
	while(x1 >= x2 && y1 >= y2)
	{
		if(y1 == 31)
		{
			y1 = 0;
			x1++;
		}
		else
			y1++;

			phys_bitmap[x1] = phys_bitmap[x1] - (1 << y1);
	}
}




/** Find first free space in allocation table */
uint32_t 
phys_first_free_alloc()
{
	uint32_t x;

	for(x = 0; x < PHYS_MAX_BLOCKS; x++)
		if(phys_allocated[x].dim == 0) 
			return x;

	return -1;
}



/** Initialize physical memory manager */
void 
phys_init(uint32_t mem)
{
	unsigned x;
	
	phys_total = mem;
	
	// Calcoliamo il numero delle pagine
	phys_page_number = ((((unsigned) phys_total / PHYS_PAGE_SIZE) / 32) * 32);
	
	// Azzeriamo la bitmap
	for(x = 0; x < (phys_page_number / 32); x++)
			phys_bitmap[x] = 0;
			
	// Azzera la tabella delel allocazioni
	for(x = 0; x < PHYS_MAX_BLOCKS; x++)
		phys_allocated[x].dim = 0;
	
	// Area per rom, etc (primo mb)
	phys_reserve(0x00000000, 0x000FFFFF);
	// Riservata per i moduli
	phys_reserve(0x00100000, 0x003FFFFF);
	// Possibile uso per hardware mappati
	phys_reserve(0x00F00000, 0x00FFFFFF);
	// Usata dai driver ( a volte )
	phys_reserve(0x0C000000, 0x0FFFFFFF); 

}
