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
#include <arch.h>
#include "multiboot.h"
#include "archinc.h"
#include "dt.h"
#include <types.h>
#include <stdio.h>

int mem = 0;
extern int main();
extern void syscallisr();
multiboot_info_t *multiboot;
void kkeyb_callback(regs_t *);

extern void *Instance;

void 
__start(multiboot_info_t *mb)
{
	mem = mb->mem_lower + mb->mem_upper;
	arch_info.mem_size = mem;
	multiboot = mb;
	arch_info.mods_pointer = (uint32_t *) mb->mods_addr;
	arch_info.mods_count = mb->mods_count;
	
	if(mb->vbe_control_info != 0)
	{
		arch_info.video_mode = VIDEO_MODE_GRAPH;
	}
	else
	{
		arch_info.video_mode = VIDEO_MODE_TEXT;
	}
	
	asm("cli");

	gdt_install();
	idt_install();
	isrs_install();
	irq_install();	
	timer_init();
	clock_init();

	handler_reg(1, &kkeyb_callback);

    //idt_set_gate(SYSCALL_INT, (uint32_t) syscallisr /*_handler*/, 0x08, 0x8E);
	asm("sti");
	
	main();
}


uint64_t 
arch_mem_total()
{	
	return mem;
}

uint8_t 
arch_init()
{
	return 0;
}


void 
arch_shutdown()
{

}



void 
arch_reboot()
{
	char temp;
	do
	{
		temp = io_inb(0x64);
		if((temp & 0x01) != 0)
		{
			(void)io_inb(0x60);
			continue;
		}
	} while((temp & 0x02) != 0);

	io_outb(0x64, 0xFE);
	while(1);
}


void 
arch_standby()
{

}




void
arch_crit_end()
{ 
	asm("sti"); 
}


void
arch_crit_start()
{ 
	asm("cli"); 
} 
