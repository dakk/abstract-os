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
#ifndef VFSMANAGER_HPP
#define VFSMANAGER_HPP

#include <vfs/File.hpp>
#include <ctype.h>
#include <vfs/Filesystem.hpp>
#include <Device.hpp>
#include <list.hpp>

class VFSManager
{
	public:
		VFSManager();
		~VFSManager();

		/* Filesystem related */
		bool Mount(char *path, Device *disk, char *fs);
		bool Umount(char *path);

		/* File / Dir related */
		File *getFile(char *path);
		bool Remove(char *path);
		bool Rename(char *path, char *newname);
		File *newFile(char *path);
		File *newDirectory(char *path);


		Filesystem *getPathFilesystem(char *path);
		bool readDir(char *path, ReadDir *rd, int i);


	private:
		list<Filesystem> *m_MountList;		///< List of mounted filesystem
		
};


#endif
