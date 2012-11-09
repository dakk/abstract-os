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
#include "abWidget.hpp"
#include <Managers.hpp>

abWidget::abWidget()
{
	m_isScrollable = false;

	m_GuiEnv = Managers::Instance->guiManager;
}



void
abWidget::setWindow(abWindow *w, unsigned x, unsigned y, unsigned dimx, unsigned dimy)
{
	m_DimX = dimx;
	m_DimY = dimy;
	m_PosX = x;
	m_PosY = y;
	m_Window = w;
}


bool 
abWidget::isIn(unsigned x, unsigned y)
{
	if((m_PosX < x) && (m_PosX + m_DimX > x) && 
		(m_PosY < y) && (m_PosY + m_DimY > y))
		return true;
	return false;
}


void
abWidget::clickEvent(unsigned key)
{
	//m_GuiEnv->drawText("Click", 100,100,0xFF);
}




bool
abWidget::getScrollable()
{
	return m_isScrollable;
}


void 
abWidget::setScrollable(bool state)
{
	m_isScrollable = state;
}



void
abWidget::setSize(unsigned x, unsigned y)
{
	m_DimX = x;
	m_DimY = y;
}

void 
abWidget::setSizeX(unsigned x)
{
	m_DimX = x;
}


void 
abWidget::setSizeY(unsigned y)
{
	m_DimY = y;
}

