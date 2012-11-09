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
#ifndef ABLABEL_HPP
#define ABLABEL_HPP

#include "abWidget.hpp"

class abLabel : public abWidget
{
	public:
		abLabel(char *text);
		virtual void Draw();
		void setText(char *text);

		
		virtual unsigned getSizeX();
		virtual unsigned getSizeY();


	protected:
		char m_Text[200];

};


#endif
