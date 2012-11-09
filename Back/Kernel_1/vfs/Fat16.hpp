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
#ifndef FAT16_HPP
#define FAT16_HPP

#include <vfs/Filesystem.hpp>
#include <ctype.h>




/** Fat16 filesystem */
class Fat16 : public Filesystem
{
	public:
		/** Fat boot record (move to Fat.hpp) */
		typedef struct
		{
			uint8_t 	jumper[3];
			uint8_t 	oem_identifier[8];
			uint16_t 	bytes_per_sector;
			uint8_t 	sector_per_cluster;
			uint16_t 	reserved_sectors;
			uint8_t 	fat_number;
			uint16_t 	dir_entry_number;
			uint16_t 	total_sectors;
			uint8_t 	media_desc_type;
			uint16_t 	sectors_per_fat;
			uint16_t 	sectors_per_track;
			uint16_t 	heads_number;
			uint32_t 	hidden_sectors;
			uint32_t 	sectors;
		} BiosParam;

		/** Fat16 extended boot record */
		typedef struct
		{
			uint8_t 	driver_number;
			uint8_t 	flags;
			uint8_t 	signature;
			uint32_t 	volume_id;
			uint8_t 	volume_label[11];
			uint8_t 	system_identifier[8];
			uint8_t 	boot_code[448];
			uint16_t	bootable_signature;
		} ExtendedBoot;

		/** Total fat16 boot header */
		typedef struct
		{
			BiosParam 		bpb;
			ExtendedBoot 	ebr;
		} BootRecord;


		Fat16(char *path, Device *dev) : Filesystem(path, dev){}
		~Fat16(){}

		virtual bool Mount();
		virtual bool Umount();		
		virtual bool readDir(ReadDir *rd, File *dir, int i);
		virtual File *getFileFromId(ReadDir *rd);

		
		virtual uint32_t Write(File *file, char *data, uint32_t size, uint64_t offset);
		virtual uint32_t Read(File *file, char *data, uint32_t size, uint64_t offset);

		virtual uint64_t getTotalSpace();
		virtual uint64_t getUsedSpace();


	private:
		uint8_t *m_FatTable;
		unsigned m_FatSize;
		unsigned m_Sectors;
		unsigned m_RootDirSectors;
		unsigned m_FirstDataSector;
		unsigned m_ClusterSize;
		unsigned m_Clusters;
};

#endif
