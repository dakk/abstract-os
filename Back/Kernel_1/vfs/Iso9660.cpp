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
#include <vfs/Iso9660.hpp>
#include <vfs/File.hpp>
#include <stdio.h>
#include <arch.h>


bool
Iso9660::Mount()
{
	ReadDir rd;	
	Iso9660::PrimaryVolumeDescriptor *d = (PrimaryVolumeDescriptor *) malloc(sizeof(PrimaryVolumeDescriptor));
	unsigned i;
	bool f;


	/* Read the bootrecord and find the first block */	
	i = 0;
	f = false;

	while((!f) && (i < 2048 * 64))
	{
		m_Disk->getDriver()->Read((uint8_t *) d, 2048, i);

		if(	(d->Identifier[0] == 'C') && (d->Identifier[1] == 'D') && 
			(d->Identifier[2] == '0') && (d->Identifier[3] == '0') && 
			(d->Identifier[4] == '1') )
			{
				if(d->Type == TC_PRIMARY_VOLUME)
					f = true;
			}

		i += 2048;
	}

	if(!f)
		return false;

	//pd = (PrimaryVolumeDescriptor *) &d;
#if 0
	int k = 0;
	uint8_t pte[2048];
	
		m_Disk->getDriver()->Read((uint8_t *) pte, 2048, 2048*4);
		int j;
		/* Allocate and read the path table */
		for(j = 0; j < 2048; j++)
		{
		//if(pd->Identifier[i] >= 'A')
				//putchar(((char *) pte)[i]);
				putchar(pte[j]); //((char *) pte)[j] << 8 | ((char *) pte)[1+j]);

				if((pte[j] == 'O') && (pte[j+1] == 'O'))
				{
					printf("%d\n", k);
					break;
				}
				arch_sleep(2000);
		}
#endif	
	/*
	m_PathTableSize = 0;

	for(i = 0; i < 8; i++)
		m_PathTableSize += pd->PathTableSize[i];

	m_PathTable = (void *) malloc(m_PathTableSize);
	m_Disk->getDriver()->Read((uint8_t *) m_PathTable, m_PathTableSize, pd->PathLTableLocation);
 */
	/* Clear the opened file list */
	m_FileList->Clear();
 
	/* Set the root node */
	rd.Node = 0;
	m_Root = getFileFromId(&rd);

	m_isMounted = true;

	return true;
}



bool
Iso9660::Umount()
{
	m_FileList->Clear();
	delete m_Root;
	m_isMounted = false;

	return true;
}



bool 
Iso9660::readDir(ReadDir *rd, File *dir, int i)
{
	return false;
}



File *
Iso9660::getFileFromId(ReadDir *rd)
{
	return NULL;
}



uint64_t 
Iso9660::getTotalSpace()
{
	return 0;
}


uint64_t 
Iso9660::getUsedSpace()
{
	return 0;
}




uint32_t 
Iso9660::Write(File *file, char *data, uint32_t size, uint64_t offset)
{
	return 0;
}



uint32_t 
Iso9660::Read(File *file, char *data, uint32_t size, uint64_t offset)
{
	return 0;
}

