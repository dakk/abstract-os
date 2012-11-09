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
#include "abWindow.hpp"

Label::Label(char *label) : Widget()
{
	strcpy(m_Label, label);
}

void
Label::Draw()
{
	abGui->drawText(m_Label, m_Window->getPositionX() + m_PosX, 
					m_Window->getPositionY() + m_PosY, 0x0);
}

void
Label::setText(char *l)
{
	strcpy(m_Label, l);
}

char *
Label::getText()
{
	return m_Label;
}
