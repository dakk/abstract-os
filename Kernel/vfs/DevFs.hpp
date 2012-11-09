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
#ifndef DEVFS_HPP
#define DEVFS_HPP

#include <vfs/Filesystem.hpp>
#include <ctype.h>

/** \addtogroup vfs
 * @{
 */



/** Fat16 filesystem */
class DevFs : public Filesystem
{
	public:
		DevFs(char *path, Device *dev) : Filesystem(path, dev){}
		~DevFs(){}

		virtual bool Mount();
		virtual bool Umount();		
		virtual bool readDir(ReadDir *rd, File *dir, int i);
		virtual File *getFileFromId(ReadDir *rd);

		
		virtual uint32_t Write(File *file, char *data, uint32_t size, uint64_t offset);
		virtual uint32_t Read(File *file, char *data, uint32_t size, uint64_t offset);

		virtual uint64_t getTotalSpace();
		virtual uint64_t getUsedSpace();


	private:
		typedef struct
		{
			unsigned i;
		} FileData;
	
};


/** @} */


#endif
