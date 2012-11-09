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
#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include <ctype.h>
#include <Device.hpp>
#include <list.hpp>
#include <ui/Window.hpp>
#include <ui/Rendering.hpp>

/** \defgroup ui UiManager */

/** \addtogroup ui
 * @{
 */

using namespace Ui;

class UiManager
{
	public:
							UiManager();
							~UiManager();
	
		bool				Setup();
		void				mainLoop();

		bool				addWindow(Window *w);

		Rendering *			getRenderingEngine();



	private:
		Device *			m_RenderingDevice;	///< Rendering device
		list<Window> *		m_WindowList;		///< List of windows
		Window *			m_WindowActive;		///< Active window
		Rendering *			m_Rendering;		///< Rendering engine
		
};



/** @} */


#endif
