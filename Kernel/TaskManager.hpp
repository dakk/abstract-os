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

/** \defgroup task TaskManager */

/** \addtogroup task
 * @{
 */

/**
 * Task manager class
 */
class TaskManager
{
	public:
					TaskManager();
					~TaskManager();

		pid_t		Kill(pid_t pid, int signal);
		pid_t		Kill(char *name, int signal);

		pid_t		addTask(char *name, void *entry);
		pid_t		Exec(char *path, char **argv, char **env);

		pid_t		getPid();
		pid_t		Fork();

		Task *		getTask(pid_t pid);
		Task *		getTask(char *name);

		/* IPC */
		static const uint32_t IPC_DEFAULT_SIZE		=	256;

		void 		sendMessage(pid_t dest, char *data, uint32_t size = IPC_DEFAULT_SIZE);
		uint32_t 	getMessage(char *data, pid_t *sender);
		
	private:
		list<Task> *m_TaskList;			///< Task list pointer
		Task *		m_TaskCurrent;
};



/** @} */


#endif
