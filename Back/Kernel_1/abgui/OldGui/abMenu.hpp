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
#ifndef ABMENU_HPP
#define ABMENU_HPP

#include "abWidget.hpp"

class abMenu : public abWidget
{
	public:
		typedef struct MenuItem
		{
			unsigned Id;
			char Label[32];
			
			struct MenuItem *Child;
			struct MenuItem *ChildEnd;
			struct MenuItem *Next;
		} MenuItem;

		static const unsigned DEFAULT_DIM_X	=	70;
		static const unsigned DEFAULT_DIM_Y	=	25;

		abMenu();
		virtual void Draw();
		MenuItem *addItem(unsigned parent_id, MenuItem m, bool separator = false);

		
		virtual unsigned getSizeX();
		virtual unsigned getSizeY();


	protected:
		MenuItem *m_ItemList;
		MenuItem *m_LastItem;
		unsigned m_ActivedItemId;

		MenuItem *getItem(MenuItem *start, unsigned id);
};


#endif
