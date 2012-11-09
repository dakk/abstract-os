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
#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <Device.hpp>
#include <string.h>
#include <list.hpp>



/** Structure to enumerate a directory */
typedef struct
{
	uint32_t Node;					///< Node id
	char Name[256];					///< Name of the node
} ReadDir;

class File;

/** An istance of a filesystem class is a mounted filesystem */
class Filesystem
{
	public:
		/** Max size for a token */
		static const unsigned TOKEN_MAX_SIZE	=	256;



		Filesystem(char *path, Device *disk);
		~Filesystem();

		/** Mount the filesystem */
		virtual bool Mount() = 0;

		/** Umount the filesystem */
		virtual bool Umount() = 0;

		char *getPath();
		int pathSplit(char *path, char *token, int ntok);
		File *getFile(char *path, File *dir);
		File *getRoot();

		/** Read the dir and return a ReadDir struct with the i-esimo file info 
		 * 		\note this solution avoid to allocate and deallocate a file each time
		 * 			  you need to enumerate a directory */
		virtual bool readDir(ReadDir *rd, File *dir, int i) = 0;

		/** Return the File by the ReadDir struct 
		 * 		\note this function return the file object after the enumeration of a directory
		 * 		      with readdir */
		virtual File *getFileFromId(ReadDir *rd) = 0;

		virtual uint32_t Write(File *file, char *data, uint32_t size, uint64_t offset) = 0;
		virtual uint32_t Read(File *file, char *data, uint32_t size, uint64_t offset) = 0;

		/** Return the total space of the mounted filesystem */
		virtual uint64_t getTotalSpace() = 0;

		/** Return the used space of the mounted filesystem */
		virtual uint64_t getUsedSpace() = 0;
		
		Filesystem *Next;

	protected:
		bool m_isMounted;			///< Is the fs mounted?
		File *m_Root;				///< Root node
		Device *m_Disk;				///< Disk device
		char m_Path[512];			///< Mounted path
		list<File> *m_FileList;		///< Hold all opened files

};


#endif
