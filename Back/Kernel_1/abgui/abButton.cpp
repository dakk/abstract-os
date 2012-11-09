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
#include "abWindow.hpp"

Button::Button(char *label) : Widget()
{
	strcpy(m_Label, label); 
}

void
Button::Draw()
{
	abGui->drawRect(m_Window->getPositionX() + m_PosX + 1,
					m_Window->getPositionY() + m_PosY + 1,
					m_Window->getPositionX() + m_PosX + strlen(m_Label) * 8 + 3,
					m_Window->getPositionY() + m_PosY + 14,
					abGui->guiTheme->WindowBackgroundColor);

	abGui->drawLine(m_Window->getPositionX() + m_PosX,
					m_Window->getPositionY() + m_PosY,
					m_Window->getPositionX() + m_PosX ,
					m_Window->getPositionY() + m_PosY + 15,
					0xCCCCCC);


	abGui->drawLine(m_Window->getPositionX() + m_PosX,
					m_Window->getPositionY() + m_PosY,
					m_Window->getPositionX() + m_PosX + strlen(m_Label) * 8 + 5,
					m_Window->getPositionY() + m_PosY,
					0xCCCCCC);

	abGui->drawLine(m_Window->getPositionX() + m_PosX,
					m_Window->getPositionY() + m_PosY + 15,
					m_Window->getPositionX() + m_PosX + strlen(m_Label) * 8 + 5,
					m_Window->getPositionY() + m_PosY + 15,
					0x555555);

	abGui->drawLine(m_Window->getPositionX() + m_PosX + strlen(m_Label) * 8 + 5,
					m_Window->getPositionY() + m_PosY,
					m_Window->getPositionX() + m_PosX + strlen(m_Label) * 8 + 5,
					m_Window->getPositionY() + m_PosY + 15,
					0x555555);

	abGui->drawText(m_Label, m_Window->getPositionX() + m_PosX + 3, 
					m_Window->getPositionY() + m_PosY + 4, 0x0);
}

void
Button::setText(char *l)
{
	strcpy(m_Label, l);
}

char *
Button::getText()
{
	return m_Label;
}
