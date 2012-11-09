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
#include <ui/widgets/Button.hpp>
#include <Managers.hpp>
#include <ctype.h>
#include <config.h>

using namespace Ui;

Button::Button(char *text) : Widget()
{
	strcpy(m_Label, text);
}



Button::~Button()
{
}



void 
Button::Draw(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned alpha)
{
	m_Rend->drawRect(x0 + 1, y0 + 1, x0 + strlen(m_Label) * 8 + 3, y0 + 14, 0x888888);
	m_Rend->drawLine(x0, y0, x0, y0 + 15, 0xCCCCCC);
	m_Rend->drawLine(x0, y0, x0 + strlen(m_Label) * 8 + 5, y0, 0xCCCCCC);
	m_Rend->drawLine(x0, y0 + 15, x0 + strlen(m_Label) * 8 + 5, y0 + 15, 0x555555);
	m_Rend->drawLine(x0 + strlen(m_Label) * 8 + 5, y0, x0 + strlen(m_Label) * 8 + 5, y0 + 15, 0x555555);

	m_Rend->drawText(x0 + 3, y0 + 4, m_Label, 0x0);

}





