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
#ifndef ABWIDGET_HPP
#define ABWIDGET_HPP

#include <Managers.hpp>

namespace abGui
{
	class Window;

	class Widget
	{
		public:
			Widget();
			~Widget();

			virtual void Draw() = 0;


			void setSize(unsigned x, unsigned y);
			void setPosition(unsigned x, unsigned y);
			void setWindow(Window *w);
			unsigned getPosX();
			unsigned getPosY();

			Widget *Next;

		protected:
			unsigned m_PosX, m_PosY;
			unsigned m_SizeX, m_SizeY;

			abGuiManager *abGui;
			Window *m_Window;
	};
};

#endif
