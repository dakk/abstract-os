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
#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include <types.h>
#include <iostream.hpp>
#include <Task.hpp>
#include <list.hpp>


/**
 * Task manager class
 */
class TaskManager
{
	public:
		TaskManager();
		~TaskManager();

		pid_t killTask(pid_t pid);
		pid_t killTask(char *name);

		pid_t addTask(char *name, void *entry);

		
	private:
		list<Task> *m_TaskList;			///< Task list pointer
};


#endif
