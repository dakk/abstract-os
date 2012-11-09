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
#include <Task.hpp>
#include <string.h>


/** Create a task */
Task::Task(char *name)
{
	strcpy(m_Name, name);

	m_MessageList = NULL;
}	


/** Destroy a task */
Task::~Task()
{
	m_MessageList = NULL;
}


/** Kill the task */
void 
Task::Kill(){}


/** Yeld the task */
void 
Task::Yeld(){}


pid_t
Task::getPid()
{
	return m_Pid;
}




void 
Task::putMessage(char *data, uint32_t size, pid_t sender)
{
	Message *m = (Message *) malloc(sizeof(Message));
	memcpy(m->Data, data, size);
	m->Size = size;
	m->Sender = sender;
	m->Next = m_MessageList;

	m_MessageList = m;
}



uint32_t 
Task::getMessage(char *data, pid_t *pid)
{
	if(m_MessageList == NULL)
		return 0;

	Message *m;
	uint32_t size = m_MessageList->Size;
		
	memcpy(data, m_MessageList->Data, size);
	*pid = m_MessageList->Sender;

	m = m_MessageList->Next;
	free(m_MessageList);
	m_MessageList = m;

	return size;
}

