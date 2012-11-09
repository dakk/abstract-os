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
#include "abProgressBar.hpp"
#include <string.h>
#include "AbGuiManager.hpp"

abProgressBar::abProgressBar(char *text, unsigned dimx) :	abWidget()
{
	m_Percentage = 0;
	strcpy(m_Label, text);
	m_DimX = dimx;
}


void 
abProgressBar::Draw()
{
	unsigned end = m_DimX * m_Percentage / 100;

	m_GuiEnv->drawRect(m_Window->PosX + m_PosX, m_Window->PosY + m_PosY,
						m_Window->PosX + m_PosX + m_DimX, m_Window->PosY + m_PosY + m_DimY,
						abTheme::ButtonLabelColor);
	

	m_GuiEnv->drawRect(m_Window->PosX + m_PosX, m_Window->PosY + m_PosY,
						m_Window->PosX + m_PosX + m_DimX, m_Window->PosY + m_PosY + end, 
						abTheme::ButtonLabelColor, true);
	

	m_GuiEnv->drawText(	m_Label, m_PosX + m_Window->PosX + end / 2, m_PosY + m_Window->PosY + 8, 
						abTheme::ButtonLabelColor);
}




unsigned 
abProgressBar::getSizeX()
{
	return m_DimX;
}

unsigned 
abProgressBar::getSizeY()
{
	return 10;
}

		
void 
abProgressBar::setPercentage(unsigned percentage)
{
	m_Percentage = percentage;
}

unsigned 
abProgressBar::getPercentage()
{
	return m_Percentage;
}


void 
abProgressBar::setLabel(char *text)
{
	strcpy(m_Label, text);
}

