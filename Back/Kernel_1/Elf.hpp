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
#ifndef ELF_HPP
#define ELF_HPP

#include <types.h>

class Elf
{
	public:
		static const uint32_t NIDENT		=	16;
		static const uint32_t ID_MAG0		=	0;
		static const uint32_t ID_MAG1		=	1;
		static const uint32_t ID_MAG2		=	2;
		static const uint32_t ID_MAG3		=	3;
		static const uint32_t ID_CLASS		=	4;
		static const uint32_t ID_DATA		=	5;
		static const uint32_t ID_VERSION	=	6;
		static const uint32_t ID_PAD		=	7;
		static const uint32_t ID_NIDENT		=	16;


		static const uint32_t TYPE_NONE		=	0;
		static const uint32_t TYPE_REL		=	1;
		static const uint32_t TYPE_EXEC		=	2;
		static const uint32_t TYPE_DYN		=	3;
		static const uint32_t TYPE_CORE		=	4;
		static const uint32_t TYPE_LOPROC	=	0xFF00;
		static const uint32_t TYPE_HIPROC	=	0xFFFF;


		static const uint32_t MAC_NONE		=	0;
		static const uint32_t MAC_M32		=	1;
		static const uint32_t MAC_SPARC		=	2;
		static const uint32_t MAC_386		=	3;
		static const uint32_t MAC_68K		=	4;
		static const uint32_t MAC_88K		=	5;
		static const uint32_t MAC_860		=	7;
		static const uint32_t MAC_MIPS		=	8;


		static const uint32_t VER_NONE		=	0;
		static const uint32_t VER_CURRENT	=	1;


		static const uint32_t CLASS_NONE	=	0;
		static const uint32_t CLASS_32		=	1;
		static const uint32_t CLASS_64		=	2;


		static const uint32_t DATA_NONE		=	0;
		static const uint32_t DATA_2LSB		=	1;
		static const uint32_t DATA_2MSB		=	2;


		/** Elf header */
		typedef struct
		{
			char ident[NIDENT];
			uint16_t type;
			uint16_t machine;
			uint32_t version;
			uint32_t entry;
			uint32_t phoff;
			uint32_t shoff;
			uint32_t flags;
			uint16_t ehsize;
			uint16_t phentsize;
			uint16_t phnum;
			uint16_t shentsize;
			uint16_t shnum;
			uint16_t shstrndx;
		} Header;


		/** Section elf header (check size) */
		typedef struct
		{
			uint32_t name;
			uint32_t type;
			uint32_t flags;
			uint32_t addr;
			uint32_t offset;
			uint32_t size;
			uint32_t link;
			uint32_t info;
			uint32_t addr_align;
			uint32_t ent_size;
		} SectionHeader;

		
		Elf(char *data, unsigned size);
		~Elf();
		
		bool Check();
		Header *getHeader();
		SectionHeader *getSectionHeader(uint32_t i);
		int Exec(int argc = 0, char **argv = NULL);
		
	protected:
		char *m_Data;
		unsigned m_Size;
};

#endif
