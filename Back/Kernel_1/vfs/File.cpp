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
#include <vfs/File.hpp>


File::File(char *path)
{
	m_isDirectory = false;
	m_isOpen = false;
}


File::File()
{
	m_isDirectory = false;
	m_isOpen = false;
}


File::~File()
{

}


/** Return filesystem object */
Filesystem *
File::getFilesystem()
{
	return m_Filesystem;
}


/** Return true if this is a directory */
bool
File::isDirectory()
{
	return m_isDirectory;
}




/**
 * Open this file
 *
 * \return state
 */
int
File::Open(char *mode)
{
	if(m_isDirectory || m_isOpen)
		return 1;

	m_isOpen = true;
	m_Offset = 0;

	return 0;
}


/** Close this file */
void 
File::Close()
{
	m_isOpen = false;
}



/** 
 * Read a block of memory from this file
 *
 * \param buf where put data
 * \param size size of data
 * \return readed bytes
 */
uint32_t 
File::Read(char *buf, uint32_t size)
{
	if(!m_isOpen)
		return 0;

	uint32_t r = m_Filesystem->Read(this, buf, size, m_Offset);
	m_Offset += r;

	return r;
}



/**
 * Write a block of memory in this file
 *
 * \param buf where get data
 * \param size size of data
 * \return written bytes
 */
uint32_t 
File::Write(char *buf, uint32_t size)
{
	if(!m_isOpen)
		return 0;

	uint32_t r = m_Filesystem->Write(this, buf, size, m_Offset);
	m_Offset += r;

	return r;
}




/**
 * Seek in a particular position of the file
 */
int 
File::Seek(uint64_t offset, unsigned where)
{
	if(!m_isOpen)
		return 0;

	switch(where)
	{
		case SEEK_SET:
			if(offset > m_Size)
				m_Offset = m_Size;
			else
				m_Offset = offset;

			break;

		case SEEK_CUR:
			m_Offset += offset;

			if(m_Offset > m_Size)
				m_Offset = m_Size;
			
			break;

		case SEEK_END:
			if(m_Size < offset)
				m_Offset = 0;
			else
				m_Offset = m_Size - offset;

			break;
	}
	return m_Offset;
}

