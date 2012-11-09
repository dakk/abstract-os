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
#include "abMenu.hpp"
#include <string.h>
#include "AbGuiManager.hpp"

abMenu::abMenu() : abWidget()
{
	m_ItemList = m_LastItem = NULL;
	m_ActivedItemId = 0;
}




unsigned 
abMenu::getSizeX()
{
	return DEFAULT_DIM_X;
}

unsigned 
abMenu::getSizeY()
{
	return DEFAULT_DIM_Y;
}


abMenu::MenuItem *
abMenu::addItem(unsigned parent_id, MenuItem m, bool separator)
{
	MenuItem *mi = (MenuItem *) malloc(sizeof(MenuItem));

	if(mi == NULL)
		return NULL;

	memcpy((char *) mi, (char *) &m, sizeof(MenuItem));
	mi->Child = NULL;
	mi->ChildEnd = NULL;

	if(separator)
		strcpy(mi->Label, "\0\0");

	mi->Next = NULL;

	if(parent_id == 0)
	{
		if(m_ItemList == NULL)
		{
			m_ItemList = mi;
			m_LastItem = mi;
		}
		else
		{
			m_LastItem->Next = mi;
			m_LastItem = mi;
		}
	}
	else
	{
		MenuItem *parent = getItem(m_ItemList, parent_id);

		if(parent == NULL)
		{
			free(mi);
			return NULL;
		}

		if(parent->Child == NULL)
		{
			parent->Child = mi;
			parent->ChildEnd = mi;
		}
		else
		{
			parent->ChildEnd->Next = mi;
			parent->ChildEnd = mi;
		}
	}

	return mi;
}



abMenu::MenuItem *
abMenu::getItem(MenuItem *start, unsigned id)
{
	MenuItem *tmp = start;

	while(tmp != NULL)
	{
		if(tmp->Id == id)
			return tmp;
		else
		{
			MenuItem *tmp2 = getItem(tmp, id);
			if(tmp2 != NULL)
				return tmp2;
		}
		
		tmp = tmp->Next;
	}

	return tmp;
}



void
abMenu::Draw()
{
	MenuItem *m = m_ItemList;
	unsigned x = 5;

	while(m != NULL)
	{
		/* Render the item */
		if(m->Label[0] != 0)
			m_GuiEnv->drawText(m->Label, m_Window->PosX + x, m_Window->PosY + 4, abTheme::WindowTitleColor);

		x += strlen(m->Label) * 8 + 8;

		if(m->Label[0] == 0)
			m_GuiEnv->drawLine( m_Window->PosX + x - 4, m_Window->PosY, m_Window->PosX + x - 4,
								m_Window->PosY + 16, abTheme::MenuBorderColor);

		/* Draw item tree */
		if(m_ActivedItemId)
		{

		}

		/* Go to the next */
		m = m->Next;
	}

	m_GuiEnv->drawLine(	m_Window->PosX, m_Window->PosY + 16, m_Window->PosX + m_Window->DimX, 
						m_Window->PosY + 16, abTheme::MenuBorderColor);
}

