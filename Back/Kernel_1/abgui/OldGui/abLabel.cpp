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
#include "abLabel.hpp"
#include <string.h>
#include "AbGuiManager.hpp"


abLabel::abLabel(char *text) : abWidget()
{
	strcpy(m_Text, text);
}


void
abLabel::Draw()
{
	m_GuiEnv->drawText(m_Text, m_PosX + m_Window->PosX + 4, m_PosY + m_Window->PosY + 8, abTheme::ButtonLabelColor);
}


void
abLabel::setText(char *text)
{
	strcpy(m_Text, text);
}



unsigned 
abLabel::getSizeX()
{
	return 0;
}


unsigned 
abLabel::getSizeY()
{
	return 0;
}

