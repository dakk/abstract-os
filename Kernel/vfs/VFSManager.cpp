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
#include <vfs/VFSManager.hpp>
#include <ctype.h>
#include <config.h>
#include <vfs/File.hpp>
#ifdef FAT16
	#include <vfs/Fat16.hpp>
#endif
#ifdef FAT32
	#include <vfs/Fat32.hpp>
#endif
#ifdef EXT2
	#include <vfs/Ext2.hpp>
#endif
#ifdef ISO9660
	#include <vfs/Iso9660.hpp>
#endif
#ifdef TARFS
	#include <vfs/Tarfs.hpp>
#endif
#include <vfs/DevFs.hpp>
#include <stdio.h>


VFSManager::VFSManager()
{
	m_MountList = new list<Filesystem>();
}



VFSManager::~VFSManager()
{
	m_MountList->Clear();
	delete m_MountList;
}


/**
 * Create a new file
 *
 * \param dir root directory
 */
File *
VFSManager::newFile(char *path)
{
	return NULL;
}


/**
 * Get a file struct from a path
 *
 * \param path file path
 */
File *
VFSManager::getFile(char *path)
{
	Filesystem *fs = getPathFilesystem(path);

	if(fs == NULL)
		return NULL;

	/* Call the filesystem getFile to get the correct file */
	path += strlen(fs->getPath());

	return fs->getFile(path, NULL);
}



/** Return the fs of a given path */
Filesystem *
VFSManager::getPathFilesystem(char *path)
{
	Filesystem *fs = NULL;
	unsigned i = 0;

	Filesystem *tmpfs;
	unsigned len = 0;

	/* Get the filesystem with the higgher mountpath len */
	while((tmpfs = m_MountList->getNode(i)) != NULL)
	{
		if(strncmp(tmpfs->getPath(), path, strlen(tmpfs->getPath())) == 0)
		{
			if(strlen(tmpfs->getPath()) > len)
			{
				len = strlen(tmpfs->getPath());
				fs = tmpfs;
			}
		}
		i++;
	}

	return fs;
}




/** Read the i element of a path */
bool
VFSManager::readDir(char *path, ReadDir *rd, int i)
{
	Filesystem *fs = getPathFilesystem(path);
	return fs->readDir(rd, NULL, i);
}


/**
 * Create a new directory
 *
 * \param path path of the new directory
 */
File *
VFSManager::newDirectory(char *path)
{
	return NULL;
}



/** Remove a file/directory */
bool 
VFSManager::Remove(char *path)
{
	return false;
}



bool
VFSManager::Rename(char *path, char *newname)
{
	return false;
}


/** 
 * Mount a filesystem 
 *
 * \param path where mount the fs
 * \param disk device to use
 * \param fs filesystem name
 *
 * \return 0 if mounted
 */
bool
VFSManager::Mount(char *path, Device *disk, char *fs)
{
	bool state;
	Filesystem *mnt = NULL;

	if(strcmp(fs, "null") == 0)
	{
		return false;
	}
	#ifdef FAT16
	else if(strcmp(fs, "fat16") == 0)
		mnt = new Fat16(path, disk);
	#endif
	#ifdef FAT32
	else if(strcmp(fs, "fat32") == 0)
		mnt = new Fat32(path, disk);
	#endif
	#ifdef EXT2
	else if(strcmp(fs, "ext2") == 0)
		mnt = new Ext2(path, disk);
	#endif
	#ifdef ISO9660
	else if(strcmp(fs, "iso9660") == 0)
		mnt = new Iso9660(path, disk);
	#endif
	#ifdef TARFS
	else if(strcmp(fs, "tarfs") == 0)
		mnt = new Tarfs(path, disk);
	#endif
	else if(strcmp(fs, "devfs") == 0)
		mnt = new DevFs(path, disk);

	if(mnt != NULL)
		state = mnt->Mount();
	else 
		return false;

	if(!state)
	{
		delete mnt;
		return false;
	}

	m_MountList->addNode(mnt);

	return true;
}



/** Umount a mounted filesystem */
bool
VFSManager::Umount(char *path)
{
	Filesystem *tmp;
	int i = 0;

	while((tmp = m_MountList->getNode(i)) != NULL)
	{
		if(strcmp(tmp->getPath(), path) == 0)
		{
			tmp->Umount();
			m_MountList->delNode(i);
			delete tmp;
			return true;
		}

		i++;
	}

	/* not found */
	return false;
}



int 
VFSManager::Link(char *path, char *path2)
{
	return 0;
}



int 
VFSManager::Unlink(char *path)
{
	return 0;
}

