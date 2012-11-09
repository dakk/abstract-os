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

/**
 * \file kernel/arch/x86/archinc.h
 * \author Davide Gessa
 * \date 10-19-09
 */
#ifndef ARCHINC_H
#define ARCHINC_H

#include <types.h>

#define RTCaddress	0x70	///< Porta del RTC, indirizzo
#define RTCdata		0x71	///< Porta del RTC, data


void clock_init();
void timer_init();


typedef struct
{
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t ds, es, fs, gs;
	uint32_t which_int, err_code;
	uint32_t eip, cs, eflags, user_esp, user_ss;
} __attribute__((packed)) regs_t;


#endif
