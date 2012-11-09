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
#ifndef TASK_HPP
#define TASK_HPP

#include <types.h>
#include <iostream.hpp>
#include <list.hpp>

/** \addtogroup task
 * @{
 */


/** Task class */
class Task
{
	public:
		static const unsigned MESSAGE_MAX_SIZE = 512;

		typedef struct Message_p
		{
			char 				Data[MESSAGE_MAX_SIZE];
			uint32_t			Size;
			pid_t				Sender;

			struct Message_p *	Next;
		} Message;

					Task(char *name);
					~Task();

		void		Kill();
		void		Yeld();
		pid_t		getPid();

		void 		putMessage(char *data, uint32_t size, pid_t sender);
		uint32_t	getMessage(char *data, pid_t *pid);
		
		Task *		Next;					///< Next task

	private:
		char 		m_Name[128];			///< Task name
		pid_t 		m_Pid;					///< Task id

		Message *	m_MessageList;			///< Message list
};


/** @} */

#endif
