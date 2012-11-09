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
#ifndef ISO9660_HPP
#define ISO9660_HPP

#include <vfs/Filesystem.hpp>
#include <ctype.h>

/** \addtogroup vfs
 * @{
 */



/** Iso9660 filesystem */
class Iso9660 : public Filesystem
{
	public:
		typedef struct
		{
			uint8_t Type;
			char Identifier[5];
			uint8_t Version;
			uint8_t Data[2041];
		} Descriptor;

		typedef struct
		{
			uint8_t Type;
			char Identifier[5];
			uint8_t Version;
			char SystemIdentifier[32];
			char BootIdentifier[32];
			uint8_t BootSystemUse[1977];
		} BootDescriptor;

		typedef struct
		{
			uint32_t Year;
			uint16_t Month;
			uint16_t Day;
			uint16_t Hour;
			uint16_t Minute;
			uint16_t Second;
			uint16_t HundredthsSecond; // from 0 to 99
			uint8_t OffsetFromGMT;
		} DateTime;

		typedef struct
		{
			uint8_t Type;
			char Identifier[5];
			uint8_t Version;
			uint8_t Unused;
			char SystemIdentifier[32];
			char VolumeIdentifier[32];
			uint8_t Unused2[8];
			uint8_t VolumeSize[8];
			uint8_t Unused3[32];
			uint32_t VolumeSetSize;
			uint32_t VolumeSequenceNumber;
			uint32_t LogicalBlockSize;
			uint8_t PathTableSize[8];
			uint32_t PathLTableLocation;
			uint32_t PathLTableOptional;
			uint32_t PathMTableLocation;
			uint32_t PathMTableOptional;
			uint8_t DirectoryEntryRoot[34];
			char VolumeSetIdentifier[128];
			char PublisherIdentifier[128];
			char DataPreparerIdentifier[128];
			char ApplicationIdentifier[128];
			char CopyrightFileIdentifier[38];
			char AbstractFileIdentifier[36];
			char BibliographicFileIdentifier[37];
			DateTime VolumeCreationDate;
			DateTime VolumeModificationDate;
			DateTime VolumeExpirationDate;
			DateTime VolumeEffectiveDate;
			uint8_t FileStructureVersion;
			uint8_t Unused4;
			uint8_t ApplicationUsed[512];
			uint8_t Reserved[653];

		} PrimaryVolumeDescriptor;


		typedef struct
		{
			uint8_t IdentifierLen;
			uint8_t ExtendedLen;
			uint32_t ExtendedLocation;
			uint16_t ParentDirNumber;
		} PathTableEntry;

		typedef struct
		{	
			char Size;
			char SectorsInExtended;
			uint32_t FirstSectorLE;
			uint32_t FirstSectorBE;
			uint32_t LengthLow;
			uint32_t LengthHigh;
			char Years, Month, Day, Hour, Minute, Second,GMT;
			char Flags;
			char InterleaveSize;
			char InterleaveGap;
			char VolSeqNum;
		} RootDirectory;

		typedef enum
		{
			TC_BOOT	= 0,
			TC_PRIMARY_VOLUME,
			TC_SUPPLEMENTARY_VOLUME,
			TC_PARTITION_DESCRIPTOR,
			TC_TERMINATOR = 255
		} TypeCodes;


		typedef struct
		{
			char Size;
			char sectors_in_extended;
		    uint32_t FirstSectorLE; //little endian
		    uint32_t FirstSectorBE; //big endian
		    uint32_t LengthLE; //little endian
		    uint32_t LengthBE; //big endian
		    char Years, Month, Day, Hour, Minute, Second, GMT;
		    char flags;
		    char InterleaveSize;
		    char InterleaveGap;
		    uint16_t VolSeqNumLE;
		    uint16_t VolSeqNumBE;
			char IdentLength;
			char Ident[30];
		} Directory;

		Iso9660(char *path, Device *dev) : Filesystem(path, dev){}
		~Iso9660(){}

		virtual bool Mount();
		virtual bool Umount();		
		virtual bool readDir(ReadDir *rd, File *dir, int i);
		virtual File *getFileFromId(ReadDir *rd);

		
		virtual uint32_t Write(File *file, char *data, uint32_t size, uint64_t offset);
		virtual uint32_t Read(File *file, char *data, uint32_t size, uint64_t offset);

		virtual uint64_t getTotalSpace();
		virtual uint64_t getUsedSpace();


	private:
		void *m_PathTable;
		unsigned m_PathTableSize;
};



/** @} */

#endif
