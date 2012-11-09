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
#ifndef ARCH_H
#define ARCH_H


#ifdef __cplusplus
extern "C"
{
#endif

#include <types.h>
#include <config.h>

/* system arch settings, passed to main from each arch _start() */
#define VIDEO_MODE_TEXT		0
#define VIDEO_MODE_GRAPH	1

typedef struct
{
  uint32_t mod_start;
  uint32_t mod_end;
  uint32_t string;
  uint32_t reserved;
} arch_info_module_t;

typedef struct
{	
	uint8_t video_mode;
	uint32_t video_x;
	uint32_t video_y;
	uint32_t video_depth;
	
	uint32_t *mods_pointer;
	uint32_t mods_count; 
	
	uint64_t mem_size;
} arch_info_t;

/* System timedate */
typedef struct
{
	uint8_t hours;			///< Ora
	uint8_t minutes;		///< Minuti
	uint8_t seconds;		///< Secondi
	uint8_t month;			///< Mese
	uint8_t day;			///< Giorno
	uint8_t year;			///< Anno
} clock_data_t;



#ifndef __cplusplus

arch_info_t arch_info;
clock_data_t clock_data;	///< Data e ora globali

#endif


clock_data_t *arch_get_clock_data();


/* Stdio */
void arch_kputch(uint8_t, int16_t, int16_t);
uint16_t arch_kgetch();
void arch_ksetcl(uint16_t);
uint16_t arch_kgetcl();
void arch_kclear();


/* Mem */
uint64_t arch_mem_total();
int arch_paging_enable(uint32_t *page_dir);



/* Input ouput on ports */
void io_outb(uint16_t, uint8_t);
uint8_t io_inb(uint16_t);
void io_outw(uint16_t, uint16_t);
uint16_t io_inw(uint16_t);
void io_outd(uint16_t, uint32_t);
uint32_t io_ind(uint16_t);
void io_outl(uint16_t, uint64_t);
uint64_t io_inl(uint16_t);
void io_insl(uint16_t, char *, uint32_t);
void io_outsw(uint16_t, uint16_t *, uint32_t);
void io_insw(uint16_t, uint16_t *, uint32_t);

#define SYSCALL_INT		0x80


/* Handler */
#ifdef X86
	#include <../arch/x86/archinc.h>
#else
/*	typedef struct
	{
		uint32_t none;
	} regs_t;*/
#endif

void handler_reg(uint8_t, void (*)(regs_t *));
void handler_unreg(uint8_t);
void syscall_handler(regs_t *);


/* Timer and Clock */
void arch_sleep(uint32_t);
uint32_t arch_get_clock();
uint32_t arch_get_tick();


/* Arch init */
uint8_t arch_init();
void arch_shutdown();
void arch_reboot();
void arch_standby();

void arch_crit_start();
void arch_crit_end();


/* Multi cpu */
#define CPU_USED		2
#define CPU_READY		1
#define CPU_SPLEEP		3
#define CPU_NOTPRESENT	0

uint32_t cpu_get_state(uint32_t);
uint32_t cpu_get_free();
uint32_t cpu_stop(uint32_t);
uint32_t cpu_num();
uint32_t cpu_exec(uint32_t, void *);
uint32_t cpu_whake(uint32_t);
uint32_t cpu_sleep(uint32_t);
uint32_t cpu_reset(uint32_t);
uint32_t cpu_get_id();


#ifdef __cplusplus
};
#endif

#endif
