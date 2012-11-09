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
#ifndef ABGUIMANAGER_HPP
#define ABGUIMANAGER_HPP

extern "C"
{
	#include <klibc/malloc.h>
	#include <types.h>
	#include <klibc/string.h>
	#include <config.h>
}	
#include <Driver.hpp>
#include <../Drivers/Vesa/Vesa.hpp>
#include <../Drivers/Mouse/Mouse.hpp>
#include "abTheme.hpp"
#include "abWindow.hpp"

#define ABGUI_TRASP		0x60606060

/** AbGui inkernel gui */
class AbGuiManager
{
	public:
		AbGuiManager();
		~AbGuiManager();
		
		bool Probe();
		void mainLoop();
		
		abWindow *addWindow(char *name);
		void drawPixel(unsigned x, unsigned y, unsigned cl);
		void drawRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned cl, bool fill = true);
		void drawLine(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned cl);
		void drawText(char *data, unsigned x, unsigned y, unsigned cl, unsigned size = 16);
		void drawBuffer(uint32_t *data, unsigned x, unsigned y, unsigned dimx, unsigned dimy);

	private:
		VesaDriver *m_Vesa;		///< Vesa driver
		MouseDriver *m_Mouse;	///< Mouse driver
		char *m_RendBuf;		///< Render buffer
		uint32_t m_RendDim;		///< Buffer dimension
		unsigned m_Bpp;
		unsigned m_Bpsl;

		unsigned m_MouseX;
		unsigned m_MouseY;

	protected:
		void clearBuffer(unsigned x0 = 0, unsigned y0 = 0, unsigned x1 = 0, unsigned y1 = 0);
		void swapBuffer(unsigned x0 = 0, unsigned y0 = 0, unsigned x1 = 0, unsigned y1 = 0);
		
		list<abWindow> *m_WindowList;

		abWidget *m_ActiveWidget;
		abWindow *m_ActiveWindow;

};



#endif
