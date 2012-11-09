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
#include <vfs/Tarfs.hpp>
#include <vfs/File.hpp>
#include <stdio.h>
#include "../../Drivers/Ramdisk/Ramdisk.hpp"
#include <arch.h>



Tarfs::Tarfs(char *path, Device *dev) : Filesystem(path, dev)
{

}


Tarfs::~Tarfs()
{
}


bool
Tarfs::Mount()
{
	ReadDir rd;	

	/* Clear the opened file list */
	m_FileList->Clear();

	#if 0
	/* Enumerate main dir */
	int i = 0;
	printf("\n");
	while(readDir(&rd, NULL, i))
	{
		printf("\t\t%s (dir: ", rd.Name);

		File *f = getFileFromId(&rd);
		printf("%d) ", f->isDirectory());

		if(!f->isDirectory())
		{
			printf("(Size = %d)", getValue(((FileHeader) (((FileStruct *) (f->FsData))->Header)).Size, 12));
		}
		printf("\n");
/*
		if(f->isDirectory() == false)
		{
			char tmp[512];
			Read(f, tmp, 512, 0);
			printf("\t\t\t%s\n", tmp);
		}
*/
		i++;
	}
 	#endif

	/* Set the root node */
	rd.Node = 0;
	m_Root = getFileFromId(&rd);

	m_isMounted = true;

	return true;
}


/** 
 * Calculate a tar value
 *
 * \param field characters of the value
 * \param size number of chars
 */
uint64_t 
Tarfs::getValue(char *field, unsigned size)
{
	uint64_t sum = 0;
	unsigned i;

	for(i = 0; (i < size) && (field[i] != 0); i++)
	{
		sum *= 8;
		sum += field[i] - '0';
	}

	return sum;
}



bool
Tarfs::Umount()
{
	m_FileList->Clear();
	delete m_Root;
	m_isMounted = false;

	return true;
}



/**
 * /TODO Support for multiple directory levels
 */
bool 
Tarfs::readDir(ReadDir *rd, File *dir, int i)
{
	ReadDir n;
	File *f;

	if(dir == NULL)
		n.Node = i;
	else
		n.Node = i + ((FileStruct *) dir->FsData)->Id;

	rd->Node = n.Node;
	f = getFileFromId(&n);
	
	if(f == NULL)
		return false;

	strcpy(rd->Name, f->getName());

	m_FileList->delNodeByObject(f);

	return true;
}



/**
 * \TODO Support for directory levels
 */
File *
Tarfs::getFileFromId(ReadDir *rd)
{
	unsigned i;
	FileStruct *d = (FileStruct *) malloc(sizeof(FileStruct));
	uint32_t pointer = 0;
	uint32_t sum = 0;
	File *f = NULL;

	for(i = 0; i <= rd->Node; i += 1)
	{
		pointer += sum;

		m_Disk->getDriver()->Read((uint8_t *) &(d->Header), 512, pointer);

		if(d->Header.Type == FT_NORMAL)
		{
			sum = ((getValue(d->Header.Size, 12) / 512) * 512);
			if((getValue(d->Header.Size, 12) % 512) != 0)
				sum += 512;

			sum += 512;
		}
		else if((d->Header.Type == FT_DIRECTORY) || (d->Header.Type == FT_HARD_LINK) || 
				(d->Header.Type == FT_SYMBOLIC_LINK) || (d->Header.Type == FT_CHAR_SPECIAL) || 
				(d->Header.Type == FT_BLOCK_SPECIAL) || (d->Header.Type == FT_FIFO) || 
				(d->Header.Type == FT_CONTIGUOUS))
			sum = 512;
		else
			break;
	}

	if((i-1) == rd->Node)
	{
		char name[TOKEN_MAX_SIZE];
		unsigned n;
		bool dir = false;

		if(d->Header.Type == FT_DIRECTORY)
			dir = true;

		/* Get the correct token name */
		n = getTokenNumber(d->Header.Name);
		if(n != 0)	n--;
		pathSplit(d->Header.Name, name, n);


		f = new File(name, this, dir, getValue(d->Header.Size, 12));
		f->FsData = (void *) malloc(sizeof(FileStruct));
		((FileStruct *) f->FsData)->Id = rd->Node;
		((FileStruct *) f->FsData)->Offset = pointer;
		memcpy((char *) &(((FileStruct *) (f->FsData))->Header), (char *) &(d->Header), sizeof(FileHeader));

		m_FileList->addNode(f);
	}
	else
		free(d);

	return f;
}



uint64_t 
Tarfs::getTotalSpace()
{
	return ((RamdiskDriver *) m_Disk)->getSize();
}



uint64_t 
Tarfs::getUsedSpace()
{
	return getTotalSpace();
}




uint32_t 
Tarfs::Write(File *file, char *data, uint32_t size, uint64_t offset)
{
	return 0;
}



uint32_t 
Tarfs::Read(File *file, char *data, uint32_t size, uint64_t offset)
{
	FileStruct *fstruct = (FileStruct *) file->FsData;
	FileHeader *fh = &fstruct->Header;

	if((getValue(fh->Size, 12) - offset) < size)
		size = getValue(fh->Size, 12) - offset;
	
	return m_Disk->getDriver()->Read((uint8_t *) data, size, fstruct->Offset + 512);
}

