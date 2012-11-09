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
#include <TaskManager.hpp>
#include <Task.hpp>
#include <Managers.hpp>
#include <Elf.hpp>
#include <stdio.h>

TaskManager::TaskManager()
{
	m_TaskList = new list<Task>();
	m_TaskCurrent = NULL;
}

TaskManager::~TaskManager()
{
	delete m_TaskList;
}


/** Kill a task */
pid_t 
TaskManager::Kill(pid_t pid, int signal)
{
	return 0;
}


/** Kill a task with the name */
pid_t 
TaskManager::Kill(char *name, int signal)
{
	return 0;
}


/** Create a task */
pid_t 
TaskManager::addTask(char *name, void *entry)
{
	return 0;
}


pid_t
TaskManager::getPid()
{
	if(m_TaskCurrent != NULL)
		return m_TaskCurrent->getPid();
	return 0;
}


pid_t
TaskManager::Fork()
{
	return 0;
}

pid_t 
TaskManager::Exec(char *path, char **argv, char **env)
{
	File *f = Managers::Instance->vfsManager->getFile(path);

	if(f == NULL)
		return -1;
	else
	{
		if(f->Open("r"))
		{
			Elf *elf;
			unsigned size;
			char *data = (char *) malloc(f->getSize());

			size = f->Read(data, f->getSize());

			elf = new Elf(data, size);

			/* If it's not an elf file, load it as a binary */
			if(!elf->Check())
			{
				delete elf;
				void (*f)();
				f = (void(*)()) ((uint32_t) data);

				f();
			}
			else
			{
				elf->Exec(NULL, NULL);
			}
		}
	}

	return 0;
}



Task *
TaskManager::getTask(pid_t pid)
{
	return NULL;
}


Task *
TaskManager::getTask(char *name)
{
	return NULL;
}



void 
TaskManager::sendMessage(pid_t dest, char *data, uint32_t size)
{
	Task *t = getTask(dest);

	if((t != NULL) && (data != NULL))
		t->putMessage(data, size, m_TaskCurrent->getPid());
}


uint32_t 
TaskManager::getMessage(char *data, pid_t *pid)
{
	return m_TaskCurrent->getMessage(data, pid);
}

