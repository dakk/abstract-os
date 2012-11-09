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
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <ctype.h>
#include <Device.hpp>
#include <list.hpp>
#include <ui/Rendering.hpp>


/** \addtogroup ui
 * @{
 */
class UiManager;

namespace Ui
{
class Widget;

class Window
{
	public:
							Window();
							~Window();

		void				setPosition(unsigned x, unsigned y);
		void				Resize(unsigned x, unsigned y);
		void				Draw(unsigned alpha);
		void				setTitle(char *text);
		void				setWidget(Widget *w);
		void				setDecorated(bool d);
		
		Window *			Next;				///< Next window

	private:
		char				m_Title[128];

		UiManager *			m_UiMan;			///< Ui manager
		Rendering *			m_Rend;				///< Rendering engine

		unsigned			m_PosX;
		unsigned			m_PosY;
		unsigned			m_SizeX;
		unsigned			m_SizeY;

		Widget *			m_Widget;
		bool				m_Decorated;
		
};

};


/** @} */


#endif
