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



TaskManager::TaskManager()
{
	m_TaskList = new list<Task>();
}

TaskManager::~TaskManager()
{
	delete m_TaskList;
}


/** Kill a task */
pid_t 
TaskManager::killTask(pid_t pid)
{
	return 0;
}


/** Kill a task with the name */
pid_t 
TaskManager::killTask(char *name)
{
	return 0;
}


/** Create a task */
pid_t 
TaskManager::addTask(char *name, void *entry)
{
	return 0;
}
