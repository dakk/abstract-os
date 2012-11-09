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
#include <Managers.hpp>
#include <vfs/VFSManager.hpp>
#include <vfs/Filesystem.hpp>



/** Create an empty mountpoint */
Filesystem::Filesystem(char *path, Device *disk)
{
	m_Disk = disk;
	strcpy(m_Path, path);

	m_isMounted = false;
	m_FileList = new list<File>();
}


/** Destroy the filesystem */
Filesystem::~Filesystem()
{
}



/** Get the path of this mounted filesystem */
char *
Filesystem::getPath()
{
	return m_Path;
}





/** Return the token at the ntok position */
int
Filesystem::pathSplit(char *path, char *token, int ntok)
{
	uint32_t i = 0;
	int k = 0;

	while(path[i] == '/')
		i++;

	for(; i < strlen(path); i++)
	{
		if((path[i] == '/') && (path[i-1] != '/'))
			k++;

		if(k == ntok)
		{
			unsigned t = 0;
			i++;
			while((path[i] != '/') && (path[i] != 0))
			{
				token[t] = path[i];
				t++;
				i++;
			}
			token[t] = 0;
			return k;
		}
	}
	return -1;
}


/** Return the root directory */
File *
Filesystem::getRoot()
{
	return m_Root;
}


/** Get a file from a path */
File *
Filesystem::getFile(char *path, File *dir)
{
	char token[256];
	File *last;
	ReadDir rd;
	unsigned i = 0; 
	unsigned k = 0;

	if(dir == NULL)
		last = getRoot();
	else
		last = dir;

	while(pathSplit(path, token, i) != -1)
	{	
		k = 0;
		
		if(!last->isDirectory())
		{
			delete(last);
			return NULL;
		}
		while(readDir(&rd, last, k))
		{
			if(strcmp(rd.Name, token) == 0)
				break;
			k++;
		}

		delete(last);

		if(strcmp(rd.Name, token) != 0)
			return NULL;

		last = getFileFromId(&rd);

		i++; 
	}
	
	return last;
}


