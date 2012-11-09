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
#include <ui/Window.hpp>
#include <ui/widgets/Widget.hpp>
#include <Managers.hpp>
#include <ctype.h>
#include <config.h>

using namespace Ui;

Window::Window()
{
	m_UiMan = Managers::Instance->uiManager;
	m_Rend = m_UiMan->getRenderingEngine();
	m_Widget = NULL;

	setDecorated(true);
	setPosition(10, 10);
	Resize(100, 100);

	setTitle("Untitled");
}



Window::~Window()
{
}


void 
Window::setWidget(Widget *w)
{
	m_Widget = w;
}


/** Set the window title */
void
Window::setTitle(char *text)
{
	strcpy(m_Title, text);
}


/** Draw the window */
void
Window::Draw(unsigned alpha)
{
	if(m_Decorated)
	{
		m_Rend->drawRect(m_PosX, m_PosY - 17, m_PosX + m_SizeX, m_PosY - 1, 0x666666, true);
		m_Rend->drawText(m_PosX + 10, m_PosY - 12, m_Title, 0xFFFFFF);
	}
	m_Rend->drawRect(m_PosX, m_PosY, m_PosX + m_SizeX, m_PosY + m_SizeY, 0xAAAAAA, true);

	if(m_Widget != NULL)
		m_Widget->Draw(m_PosX, m_PosY, m_PosX + m_SizeX, m_PosY + m_SizeY, alpha);
}




void
Window::setDecorated(bool d)
{
	m_Decorated = d;
}


/** Set the window position */
void
Window::setPosition(unsigned x, unsigned y)
{
	m_PosX = x;
	m_PosY = y;
}


void
Window::Resize(unsigned x, unsigned y)
{
	m_SizeX = x;
	m_SizeY = y;
}

