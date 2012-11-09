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
#include <ui/widgets/Box.hpp>
#include <Managers.hpp>
#include <ctype.h>
#include <config.h>

using namespace Ui;

Box::Box(bool vertical, unsigned border) : Widget()
{
	m_Vertical = vertical;
	m_Border = border;
}



Box::~Box()
{
}



void 
Box::Draw(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned alpha)
{

}





