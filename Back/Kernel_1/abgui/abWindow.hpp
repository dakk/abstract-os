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
#ifndef ABWINDOW_HPP
#define ABWINDOW_HPP

#include "abWidget.hpp"
#include <list.hpp>

using namespace abGui;

namespace abGui
{
	class Window
	{
		public:
			Window();
			~Window();

			void setTitle(char *title);
			char *getTitle();
			void Draw();
			void addWidget(Widget *w);

			unsigned getSizeX();
			unsigned getSizeY();
			void setSize(unsigned x, unsigned y);

			bool getDecorated();
			void setDecorated(bool dec);

			bool getResizable();
			void setResizable(bool res);

			void setPosition(unsigned x, unsigned y);
			unsigned getPositionX();
			unsigned getPositionY();

			void setFullscreen(bool f);
			bool getFullscreen();

			Window *Next;

		protected:
			char m_Title[128];
			bool m_Decorated;
			bool m_Resizable;
			bool m_Fullscreen;
			unsigned m_SizeX;
			unsigned m_SizeY;
			unsigned m_PosX;
			unsigned m_PosY;

			abGuiManager *abGui;
			list<Widget> *m_WidgetList;
	};

};

#endif
