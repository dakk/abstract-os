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
#include "abText.hpp"
#include "abWindow.hpp"

Text::Text() : Widget()
{
	m_BackgroundColor = 0xFFFFFF;
}

void
Text::Draw()
{
	abGui->drawRect(m_Window->getPositionX() + m_PosX, 
					m_Window->getPositionY() + m_PosY,
					m_Window->getPositionX() + m_PosX + m_SizeX,
					m_Window->getPositionY() + m_PosY + m_SizeY, m_BackgroundColor);

	abGui->drawLine(m_Window->getPositionX() + m_PosX,
					m_Window->getPositionY() + m_PosY,
					m_Window->getPositionX() + m_PosX ,
					m_Window->getPositionY() + m_PosY + m_SizeY,
					0x555555);


	abGui->drawLine(m_Window->getPositionX() + m_PosX,
					m_Window->getPositionY() + m_PosY,
					m_Window->getPositionX() + m_PosX + m_SizeX,
					m_Window->getPositionY() + m_PosY,
					0x555555);

	abGui->drawLine(m_Window->getPositionX() + m_PosX,
					m_Window->getPositionY() + m_PosY + m_SizeY,
					m_Window->getPositionX() + m_PosX + m_SizeX,
					m_Window->getPositionY() + m_PosY + m_SizeY,
					0xCCCCCC);

	abGui->drawLine(m_Window->getPositionX() + m_PosX + m_SizeX,
					m_Window->getPositionY() + m_PosY,
					m_Window->getPositionX() + m_PosX + m_SizeX,
					m_Window->getPositionY() + m_PosY + m_SizeY,
					0xCCCCCC);
}


char *
Text::getText()
{

}



void 
Text::setBackgroundColor(unsigned cl)
{
	m_BackgroundColor = cl;
}


unsigned 
Text::getBackgroundColor()
{
	return m_BackgroundColor;
}

