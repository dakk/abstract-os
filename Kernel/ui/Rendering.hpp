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
#ifndef UIRENDERING_HPP
#define UIRENDERING_HPP

#include <ctype.h>
#include <Device.hpp>
#include <list.hpp>

class VesaDriver;

class Rendering
{
	public:
							Rendering(Device *dev);
							~Rendering();

		void				drawPixel(unsigned x, unsigned y, uint32_t color = 0);
		void				drawText(unsigned x, unsigned y, char *text, uint32_t color = 0, unsigned size = 16);
		void				drawLine(unsigned x0, unsigned y0, unsigned x1, unsigned y1, uint32_t color = 0);
		void				drawRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, 
										uint32_t color = 0, bool fill = true);
		void				drawRectGradient(unsigned x0, unsigned y0, unsigned x1, unsigned y1,
												uint32_t color1, uint32_t color2, bool rightleft = false);
		void				swapBuffer();
	


	private:
		unsigned			m_MemSize;
		char *				m_Mem; 
		Device *			m_Device;	///< Rendering device
		Driver *			m_Driver;	///< Rendering driver
		VesaDriver *		m_Vesa;

		
};



/** @} */


#endif
