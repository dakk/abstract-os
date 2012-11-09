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
#include <vfs/Fat16.hpp>
#include <vfs/File.hpp>
#include <stdio.h>


bool
Fat16::Mount()
{
	BootRecord *brec;
	ReadDir rd;
	uint32_t datasect;
	
	/* Read the bootrecord */	
	brec = (BootRecord *) malloc(sizeof(BootRecord));
	m_Disk->getDriver()->Read((uint8_t *) brec, sizeof(BootRecord), 0);

	//if((brec->ebr.signature != 0x28) && (brec->ebr.signature != 0x29))
	//	return false;

	//brec->ebr.volume_label[10] = 0;
	//printf("Fat16 '%s' '%s' \n\n", brec->ebr.volume_label, brec->bpb.oem_identifier);

	m_FatSize = brec->ebr.driver_number;
	m_Sectors = brec->bpb.sectors;
	m_RootDirSectors = ((brec->bpb.dir_entry_number * 32) + (brec->bpb.bytes_per_sector - 1)) / 
						brec->bpb.bytes_per_sector;
	m_FirstDataSector = brec->bpb.reserved_sectors + m_FatSize * brec->bpb.fat_number;
	m_ClusterSize = brec->bpb.bytes_per_sector * brec->bpb.sector_per_cluster;
	datasect = m_Sectors - (m_FirstDataSector + m_RootDirSectors);
	m_Clusters = datasect / brec->bpb.sector_per_cluster;

	/* Clear the opened file list */
	m_FileList->Clear();

	/* Set the root node */
	rd.Node = 0;
	m_Root = getFileFromId(&rd);

	m_isMounted = true;

	return true;
}



bool
Fat16::Umount()
{
	m_FileList->Clear();
	delete m_Root;
	m_isMounted = false;

	return true;
}



bool 
Fat16::readDir(ReadDir *rd, File *dir, int i)
{
	return false;
}



File *
Fat16::getFileFromId(ReadDir *rd)
{
	return NULL;
}



uint64_t 
Fat16::getTotalSpace()
{
	return 0;
}


uint64_t 
Fat16::getUsedSpace()
{
	return 0;
}




uint32_t 
Fat16::Write(File *file, char *data, uint32_t size, uint64_t offset)
{
	return 0;
}



uint32_t 
Fat16::Read(File *file, char *data, uint32_t size, uint64_t offset)
{
	return 0;
}

