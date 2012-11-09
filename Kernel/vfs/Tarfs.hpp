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
#ifndef TARFS_HPP
#define TARFS_HPP

#include <vfs/Filesystem.hpp>
#include <ctype.h>


/** \addtogroup vfs
 * @{
 */


/** Tarfs filesystem */
class Tarfs : public Filesystem
{
	public:
		typedef struct
		{
			char Name[100];
			char FileMode[8];
			char Owner[8];
			char Group[8];
			char Size[12];
			char LastModification[12];
			char CheckSum[8];
			char Type;
			char NameOfLinked[100];
		} FileHeader;

		typedef struct
		{
			FileHeader Header;
			uint32_t Id;
			uint32_t Offset;
		} FileStruct;

		typedef enum
		{
			FT_NORMAL = '0', FT_HARD_LINK, FT_SYMBOLIC_LINK, FT_CHAR_SPECIAL,
			FT_BLOCK_SPECIAL, FT_DIRECTORY, FT_FIFO, FT_CONTIGUOUS
		} FileType;

		Tarfs(char *path, Device *dev);
		~Tarfs();

		virtual bool Mount();
		virtual bool Umount();		
		virtual bool readDir(ReadDir *rd, File *dir, int i);
		virtual File *getFileFromId(ReadDir *rd);

		uint64_t getValue(char *field, unsigned size);


		
		virtual uint32_t Write(File *file, char *data, uint32_t size, uint64_t offset);
		virtual uint32_t Read(File *file, char *data, uint32_t size, uint64_t offset);

		virtual uint64_t getTotalSpace();
		virtual uint64_t getUsedSpace();


	private:
		void *m_PathTable;
		unsigned m_PathTableSize;
};



/** @} */


#endif
