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
#include <arch.h>
#include <types.h>

#define VIDEO_MEM 	((volatile uint16_t*)0x6000000)


#define PUTPIXEL(x, y, c) VIDEO_MEM[(y * 240) + x] = c;

#define VIDEO_X 240
#define VIDEO_Y 320

/*
void render_write_letter(char letter, uint32_t col, uint32_t x, uint32_t y)
{
	int i;
	int j;
	
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < 8; j++)
		{			
			if((let_data[i] & (1 << j)) > 0)
				render_draw_pixel(x+j, y+i-4, (uint32_t) col);
		}
	}
}
*/

/* set a color */
void 
arch_ksetcl(uint16_t cl)
{
}


/* clear */
void 
arch_kclear()
{
	int i,j;
	for(i = 0; i < VIDEO_X; i++)
		for(j = 0; j < VIDEO_Y; j++)
			PUTPIXEL(i, j, 0);
}


/* */
uint16_t 
arch_kgetch()
{
	return 0;
}


void
arch_kputch(uint8_t ch, int16_t x, int16_t y)
{

}
