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
#include "abTheme.hpp"
#include <types.h>

#define B 0x60606060

using namespace abGui;

Theme::Theme()
{
	uint32_t cursor[][12] =
	{
		{ 0, B, B, B, B, B, B, B, B, B, B, 0 },
		{ B, 0, B, B, B, B, B, B, B, B, 0, B },
		{ B, B, 0, B, B, B, B, B, B, 0, B, B },
		{ B, B, B, 0, B, B, B, B, 0, B, B, B },
		{ B, B, B, B, 0, B, B, 0, B, B, B, B },
		{ B, B, B, B, B, 0, 0, B, B, B, B, B },
		{ B, B, B, B, B, 0, 0, B, B, B, B, B },
		{ B, B, B, B, 0, B, B, 0, B, B, B, B },
		{ B, B, B, 0, B, B, B, B, 0, B, B, B },
		{ B, B, 0, B, B, B, B, B, B, 0, B, B },
		{ B, 0, B, B, B, B, B, B, B, B, 0, B },
		{ 0, B, B, B, B, B, B, B, B, B, B, 0 }
	};

	CursorImage = new Image((void *) cursor, 12, 12, 4);


	uint32_t panel[][1] = 
	{
		{ 0x00C6C6C6 } ,
		{ 0x00C4C4C4 } ,
		{ 0x00C2C2C2 } ,
		{ 0x00BFBFBF } ,
		{ 0x00BDBDBD } ,
		{ 0x00BBBBBB } ,
		{ 0x00B9B9B9 } ,
		{ 0x00B7B7B7 } ,
		{ 0x00B5B5B5 } ,
		{ 0x00B3B3B3 } ,
		{ 0x00B3B3B3 } ,
		{ 0x00B5B5B5 } ,
		{ 0x00B7B7B7 } ,
		{ 0x00B9B9B9 } ,
		{ 0x00BBBBBB } ,
		{ 0x00BDBDBD } ,
		{ 0x00BFBFBF } ,
		{ 0x00C2C2C2 } ,
		{ 0x00C4C4C4 } ,
		{ 0x00C6C6C6 }
	};
	PanelImage = new Image((void *) panel, 1, 20, 4);
	BackgroundColor = 0x643979;//0x785b9b;

	WindowBackgroundColor = 0xAAAAAA;
}

Theme::Theme(char *theme_dir)
{

}


Theme::~Theme()
{

}
