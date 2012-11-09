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
#ifndef ABPROGRESSBAR_HPP
#define ABPROGRESSBAR_HPP

#include "abWidget.hpp"

class abProgressBar : public abWidget
{
	public:
		abProgressBar(char *text, unsigned dimx);
		virtual void Draw();
		void setPercentage(unsigned percentage);
		unsigned getPercentage();
		void setLabel(char *text);

		
		virtual unsigned getSizeX();
		virtual unsigned getSizeY();


	protected:
		unsigned m_Percentage;
		char m_Label[128];

};

#endif
