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

#include <types.h>

class abWindow;
class AbGuiManager;

class abWidget
{
	public:
		abWidget();
		virtual void Draw() = 0;
		bool isIn(unsigned x, unsigned y);

		virtual void clickEvent(unsigned key);
		virtual void keyEvent(uint32_t c){};

		bool getScrollable();
		void setScrollable(bool state);

		virtual unsigned getSizeX() = 0;
		virtual unsigned getSizeY() = 0;

		void setSize(unsigned x, unsigned y);
		void setSizeX(unsigned x);
		void setSizeY(unsigned y);
		void setWindow(abWindow *w, unsigned x, unsigned y, unsigned dimx, unsigned dimy);

		abWidget *Next;

	protected:
		abWindow *m_Window;
		bool m_isScrollable;
		
		unsigned m_DimX;
		unsigned m_DimY;
		unsigned m_PosX;
		unsigned m_PosY;

		AbGuiManager *m_GuiEnv;
};

#endif
