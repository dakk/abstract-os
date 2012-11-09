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
#include <vfs/Filesystem.hpp>
#include <vfs/DevFs.hpp>
#include <vfs/File.hpp>
#include <stdio.h>
#include <Managers.hpp>


bool
DevFs::Mount()
{
	ReadDir rd;

	/* Clear the opened file list */
	m_FileList->Clear();

	/* Set the root node */
	rd.Node = 0;
	m_Root = getFileFromId(&rd);

	m_isMounted = true;

	return true;
}



bool
DevFs::Umount()
{
	m_FileList->Clear();
	delete m_Root;
	m_isMounted = false;

	return true;
}



bool 
DevFs::readDir(ReadDir *rd, File *dir, int i)
{
	Device *d = Managers::Instance->deviceManager->getDevice(i);

	if(d == NULL)
		return false;

	strcpy(rd->Name, d->getName());
	rd->Node = i;

	return true;
}



File *
DevFs::getFileFromId(ReadDir *rd)
{
	File *f = new File();

	if(f == NULL)
		return f;

	f->FsData = (void *) malloc(sizeof(FileData));
	if(f->FsData == NULL)
	{
		delete f;
		return NULL;
	}

	((FileData *) f->FsData)->i = rd->Node;
	
	m_FileList->addNode(f);

	return f;
}



uint64_t 
DevFs::getTotalSpace()
{
	return getUsedSpace();
}


uint64_t 
DevFs::getUsedSpace()
{
	return Managers::Instance->deviceManager->getDevicesNumber() * sizeof(Device);
}




uint32_t 
DevFs::Write(File *file, char *data, uint32_t size, uint64_t offset)
{
	Device *d = Managers::Instance->deviceManager->getDevice(((FileData *) file->FsData)->i);

	if(d == NULL)
		return 0;

	return d->getDriver()->Write((uint8_t *) data, size, offset);
}



uint32_t 
DevFs::Read(File *file, char *data, uint32_t size, uint64_t offset)
{
	Device *d = Managers::Instance->deviceManager->getDevice(((FileData *) file->FsData)->i);

	if(d == NULL)
		return 0;

	return d->getDriver()->Read((uint8_t *) data, size, offset);
}

