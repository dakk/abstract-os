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
#ifndef __MULTIBOOT_H
#define __MULTIBOOT_H

#include <types.h>

/** Structure of a multiboot module */
typedef struct multiboot_module
{
  unsigned long mod_start;
  unsigned long mod_end;
  unsigned long string;
  unsigned long reserved;
} multiboot_module_t;


/** Structure of the multiboot header */
typedef struct multiboot_info
{
	uint32_t flags;					///< Flag del bootloader
	uint32_t mem_lower;				///< Memoria bassa
	uint32_t mem_upper;				///< Memoria alta
	uint32_t boot_device;			///< Dispositivo di boot
	uint32_t cmdline;				///< Argomenti passati al kernel
	uint32_t mods_count;			///< Grandezza modulo
	uint32_t mods_addr;				///< Indirizzo di ubicazione del modulo
	
	// Elf Info
	uint32_t elf_num;
	uint32_t elf_size;
	uint32_t elf_addr;
	uint32_t elf_shndx;

	uint32_t mmap_length;			
	uint32_t mmap_addr;
	uint32_t drives_length;
	uint32_t drives_addr;
	uint32_t config_table;
	
	uint32_t boot_loader_name;		///< Nome del bootloader
	uint32_t apm_table;				///< Tabella specifiche apm
	uint32_t vbe_control_info;		///< Struttura controllo vesa bios
	uint32_t vbe_mode_info;			///< Struttura info vesa bios
	uint32_t vbe_mode;				///< Modalita vesa bios attiva
	uint32_t vbe_interface_seg;		///< Segmento interfaccia vesa bios
	uint32_t vbe_interface_off;		///< Offset interfaccia vesa bios
	uint32_t vbe_interface_len;		///< Lunghezza interfaccia vesa bios
} __attribute__((packed)) multiboot_info_t;

#endif
