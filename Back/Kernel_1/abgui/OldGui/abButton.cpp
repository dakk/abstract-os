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
#include "abButton.hpp"
#include <string.h>
#include "AbGuiManager.hpp"


abButton::abButton(char *name) : abWidget()
{
	strcpy(m_Label, name);
}


void
abButton::Draw()
{
	unsigned k;
	unsigned end = strlen(m_Label) * 8 + 8;

	
	unsigned j = abTheme::Smooth;
	for(k = 0; k < end; k++, k < abTheme::Smooth+1 ? j-- : j, k > (end - (abTheme::Smooth + 1)) ? j++ : j)
	{ 
		m_GuiEnv->drawBuffer((uint32_t *) abTheme::ButtonDecorator, m_Window->PosX + m_PosX + k, 
								m_Window->PosY + j + m_PosY, 1, abTheme::ButtonDecoratorSizeY - j * 2);
	}

	m_GuiEnv->drawText(m_Label, m_PosX + m_Window->PosX + 4, m_PosY + m_Window->PosY + 8, abTheme::ButtonLabelColor);
}




unsigned 
abButton::getSizeX()
{
	return DEFAULT_DIM_X;
}

unsigned 
abButton::getSizeY()
{
	return DEFAULT_DIM_Y;
}

