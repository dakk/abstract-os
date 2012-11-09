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
#ifndef FILE_HPP
#define FILE_HPP

#include "Filesystem.hpp"

class File
{
	public:
		static const unsigned SEEK_SET =	0x1;
		static const unsigned SEEK_CUR =	0x2;
		static const unsigned SEEK_END =	0x3;


		File();
		File(char *path);
		~File();
		Filesystem *getFilesystem();
		bool isDirectory();

		int Open(char *mode);
		void Close();
		uint32_t Read(char *buf, uint32_t size);
		uint32_t Write(char *buf, uint32_t size);
		int Seek(uint64_t offset, unsigned where);

		File *Next;
		void *FsData;			///< Space for struct allocated by the fs
		
	protected:
		uint64_t m_Offset;
		uint64_t m_Size;

		Filesystem *m_Filesystem;
		bool m_isDirectory;
		bool m_isOpen;
};

#endif
