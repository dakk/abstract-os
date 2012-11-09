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
#ifndef ABTHEME_HPP
#define ABTHEME_HPP


#include <types.h>

class abTheme
{
	public:
		static const char DefaultFont8x16[][16];
		static const char DefaultFont8x8[][8];

		static const unsigned PointerSizeX = 16;
		static const unsigned PointerSizeY = 16;
		static const uint32_t Pointer[][16];
	
		static const unsigned WindowDecoratorSize = 15;

		static const uint32_t WindowDecorator[][1];

		static const unsigned ButtonDecoratorSizeY	= 20;

		static const uint32_t ButtonDecorator[][1];

		static const uint32_t Smooth = 1;
		static const uint32_t WindowTitleColor = 0x555555;

		static const uint32_t ButtonLabelColor = WindowTitleColor;
		static const uint32_t WindowBackColor = 0xAAAAAA;
		static const uint32_t WindowBorderColor = WindowBackColor;
		static const uint32_t EntryBackColor = 0xDDDDDD;
		static const uint32_t MenuBorderColor = 0x999999;
};

#endif
