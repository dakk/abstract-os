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
#include "abTextEntry.hpp"
#include <string.h>
#include "AbGuiManager.hpp"


abTextEntry::abTextEntry() : abWidget()
{
}



void
abTextEntry::Draw()
{
	m_GuiEnv->drawRect(	m_PosX + m_Window->PosX, m_PosY + m_Window->PosY + 1, 
						m_PosX + m_Window->PosX + m_DimX, m_PosY + m_Window->PosY + m_DimY - 1, 
						abTheme::EntryBackColor);

	m_GuiEnv->drawLine( m_PosX + 1 + m_Window->PosX, m_PosY + m_Window->PosY,
						m_PosX - 1 + m_Window->PosX + m_DimX, m_PosY + m_Window->PosY, 
						abTheme::EntryBackColor);

	
	m_GuiEnv->drawLine( m_PosX + 1 + m_Window->PosX, m_PosY + m_Window->PosY + m_DimY - 1,
						m_PosX - 1 + m_Window->PosX + m_DimX, m_PosY + m_Window->PosY + m_DimY - 1,
						abTheme::EntryBackColor);

	//m_GuiEnv->drawText(m_Text, m_PosX + m_Window->PosX + 4, m_PosY + m_Window->PosY + 8, 
	//					abTheme::ButtonLabelColor);
}




unsigned 
abTextEntry::getSizeX()
{
	return m_DimX;
}

unsigned 
abTextEntry::getSizeY()
{
	return m_DimY;
}

