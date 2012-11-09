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
#include <mm/paging.h>
#include <Managers.hpp>



unsigned int page_aligned_end = (((unsigned int) /*end*/ 0x00FFFFF) & 0xFFFFF000) + 0x1000;
unsigned int *page_directory = (unsigned int*) page_aligned_end;



/** Alloc a virtual address */
void *
paging_alloc(void *v_addr, uint32_t flags)
{
	return NULL;
}


/** Alloc a virtual address for a task */
void *
paging_palloc(pid_t task, void *v_addr, uint32_t flags)
{
	Task *t = Managers::Instance->taskManager->getTask(task);

	if(t == NULL)
		return NULL;

	return NULL;
}


/** Map a physical address to a virtual address */
void *
paging_map(void *p_addr, void *v_addr, uint32_t flags)
{
	return NULL;
}
	


/** Map a physical address to a virtual address for a task */
void *
paging_pmap(pid_t task, void *p_addr, void *v_addr, uint32_t flags)
{
	Task *t = Managers::Instance->taskManager->getTask(task);

	if(t == NULL)
		return NULL;

	return NULL;
}


/** Release all pages allocated for one task */
void 
paging_prelease(pid_t task)
{
	Task *t = Managers::Instance->taskManager->getTask(task);

	if(t == NULL)
		return;
}



/** Enable paging support */
void 
paging_init()
{
	int i;

	/* Clean pagedir */
	for(i = 0; i < 1024; i++)
	    page_directory[i] = 0 | 2; 


	/* Create a page table */
	unsigned int *first_page_table = page_directory + 0x1000;
	unsigned int address = 0; 
 
	for(i = 0; i < 1024; i++)
	{
	    first_page_table[i] = address | 3;
	    address = address + 4096;
	}

	/* Enable paging */
	arch_paging_enable(page_directory);
}

