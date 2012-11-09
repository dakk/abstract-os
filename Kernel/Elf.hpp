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


		typedef enum { MAC_NONE = 0, MAC_M32, MAC_SPARC, MAC_386, MAC_68K, MAC_88K, MAC_860	= 7, MAC_MIPS } Machine;


		static const uint32_t VER_NONE		=	0;
		static const uint32_t VER_CURRENT	=	1;


		typedef enum { CLASS_NONE = 0, CLASS_32, CLASS_64 } Class;


		static const uint32_t DATA_NONE		=	0;
		static const uint32_t DATA_2LSB		=	1;
		static const uint32_t DATA_2MSB		=	2;


		/** Elf header */
		typedef struct
		{
			char Ident[NIDENT];
			uint16_t Type;
			uint16_t Machine;
			uint32_t Version;
			uint32_t Entry;
			uint32_t PhOff;
			uint32_t ShOff;
			uint32_t Flags;
			uint16_t EhSize;
			uint16_t PhEntSize;
			uint16_t PhNum;
			uint16_t ShEntSize;
			uint16_t ShNum;
			uint16_t ShStrndx;
		} Header;


		/** Section elf header (check size) */
		typedef struct
		{
			uint32_t Name;
			uint32_t Type;
			uint32_t Flags;
			uint32_t Addr;
			uint32_t Offset;
			uint32_t Size;
			uint32_t Link;
			uint32_t Info;
			uint32_t AddrAlign;
			uint32_t EntSize;
		} SectionHeader;

		typedef struct
		{
			uint32_t Offset;
			uint32_t Info;
		} RelocEntry;

		typedef struct
		{
			RelocEntry Reloc;
			uint32_t Addend;
		} RelocAddendEntry;

						Elf(char *data, unsigned size);
						~Elf();
		
		bool			Check();
		Header *		getHeader();
		SectionHeader *	getSectionHeader(uint32_t i);

		unsigned		Relocate32();
		void *			getEntry();
		int 			Exec(char **argv = NULL, char **env = NULL);

		void 			printInfo();
		
	protected:
		char *			m_Data;
		unsigned 		m_Size;
};

#endif
