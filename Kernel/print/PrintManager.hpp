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
#ifndef PRINTMANAGER_HPP
#define PRINTMANAGER_HPP

#include <iostream.hpp>
#include <Driver.hpp>
#include <list.hpp>


/** \defgroup print PrintManager */

/** \addtogroup print
 * @{
 */


/** A print job */
class PrintJob
{
	public:
		typedef enum 	Priority 
			{ PRIORITY_HIGH, PRIORITY_NORMAL, PRIORITY_LOW };
		
						PrintJob(Priority p);
						~PrintJob();
	
	private:
		Priority		m_Priority;				///< Priority
};



/** General class to handle printing job of the system */
class PrintManager
{
	public:
						PrintManager();
						~PrintManager();
};



/** @} */

#endif
