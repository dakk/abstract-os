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
#include <Drivers/Vesa/Vesa.hpp>
#include <Drivers/Mouse/Mouse.hpp>
#include <list.hpp>
#include <config.h>
#include "abTheme.hpp"
#include "abImage.hpp"
//#include "abWindow.hpp"

#define ABGUI_TRASP		0x60606060

using namespace abGui;

namespace abGui
{
	class Window;
	class Loader;
};

/** AbGui inkernel gui */
class abGuiManager
{
	public:
		abGuiManager();
		~abGuiManager();
		
		bool Init();
		bool Probe();
		void mainLoop();
		
		void appendWindow(Window *w);
		void drawPixel(unsigned x, unsigned y, unsigned cl);
		void drawRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned cl, bool fill = true);
		void drawGradientRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned start, unsigned end, bool lr);
		void drawLine(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned cl);
		void drawText(char *data, unsigned x, unsigned y, unsigned cl);
		void drawBuffer(uint32_t *data, unsigned x, unsigned y, unsigned dimx, unsigned dimy);
		void drawImage(Image *i, unsigned x, unsigned y);
		void clearBuffer(unsigned x0 = 0, unsigned y0 = 0, unsigned x1 = 0, unsigned y1 = 0);
		void swapBuffer(unsigned x0 = 0, unsigned y0 = 0, unsigned x1 = 0, unsigned y1 = 0);
		
		Theme *guiTheme;

		list<Window> *getCurrentWindowList();

		unsigned SizeX;
		unsigned SizeY;

		#ifdef ABGUI_LOADER
			Loader *guiLoader;
		#endif

	private:
		list<Window> *m_WindowList[4];
		unsigned m_ActiveDesktop;

		VesaDriver *m_Vesa;		///< Vesa driver
		MouseDriver *m_Mouse;	///< Mouse driver
		char *m_RendBuf;		///< Render buffer
		uint32_t m_RendDim;		///< Buffer dimension
		unsigned m_Bpp;
		unsigned m_Bpsl;

		unsigned m_MouseX;
		unsigned m_MouseY;
};



#endif
