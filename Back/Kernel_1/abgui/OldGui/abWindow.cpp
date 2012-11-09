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
#include "abWindow.hpp"
#include "abWidget.hpp"
#include "abButton.hpp"
#include "abLabel.hpp"
#include <Managers.hpp>

 
abWindow::abWindow(char *name)
{
	m_WidgetList = new list<abWidget>();

	DimX = START_DIM_X;
	DimY = START_DIM_Y;
	PosX = START_POS_X;
	PosY = START_POS_Y;
	m_isDecorated = true;
	m_NeedUpdate = true;

	strcpy(m_Title, name);

	m_GuiEnv = Managers::Instance->guiManager;
}



abWidget *
abWindow::clickEvent(unsigned x, unsigned y, unsigned key)
{
	abWidget *w = m_WidgetList->getNode(0);

	while(w != NULL)
	{
		if(w->isIn(x, y))
		{
			w->clickEvent(key);
			return w;
		}
		w = w->Next;
	}

	return NULL;
}


void
abWindow::setDecorated(bool state)
{
	m_isDecorated = state;
}


void
abWindow::Draw()
{	
	/*
	if(!m_NeedUpdate)
		return;
*/
	//m_NeedUpdate = false;

	/* Draw window background */
	m_GuiEnv->drawRect(PosX, PosY, PosX + DimX, PosY + DimY, abTheme::WindowBackColor);


	/* Draw window decorations */
	if(m_isDecorated)
	{
		register unsigned k;
		register unsigned j = abTheme::Smooth;
		
		for(k = 0; k < DimX; k++, k < abTheme::Smooth + 1 ? j-- : j, k > (DimX - (abTheme::Smooth + 1)) ? j++ : j)
		{ 
			m_GuiEnv->drawBuffer((uint32_t *) abTheme::WindowDecorator, PosX + k, 
									j + PosY - abTheme::WindowDecoratorSize, 
									1, abTheme::WindowDecoratorSize - j);
		}

		m_GuiEnv->drawText(m_Title, PosX + 3, PosY - 10, abTheme::WindowTitleColor);
		//m_GuiEnv->drawLine(PosX, PosY, PosX + DimX, PosY, abTheme::WindowBorderColor);
		//m_GuiEnv->drawLine(PosX + abTheme::Smooth, PosY + DimY, PosX + DimX - abTheme::Smooth, PosY + DimY, 
		//					abTheme::WindowBorderColor);

		m_GuiEnv->drawText("_x", PosX + DimX - 16, PosY - 10, abTheme::WindowTitleColor);
	}

	/* Draw all widgets */
	register abWidget *tmp = m_WidgetList->getNode(0);

	while(tmp != NULL)
	{
		tmp->Draw();
		tmp = tmp->Next;
	}

}

abWindow::~abWindow()
{
	m_WidgetList->Clear();
	delete m_WidgetList;
}



void 
abWindow::setSize(unsigned x, unsigned y)
{
	DimX = x;
	DimY = y;
}


void 
abWindow::setPosition(unsigned x, unsigned y)
{
	PosX = x;
	PosY = y;
}


void 
abWindow::setTitle(char *name)
{
	strcpy(m_Title, name);
}





void 
abWindow::addWidget(abWidget *w, unsigned x, unsigned y)
{
	if(w == NULL)
		return;

	w->setWindow(this, x, y, w->getSizeX(), w->getSizeY());

	m_WidgetList->addNode(w);
}



bool
abWindow::getDecorated()
{
	return m_isDecorated;
}


char *
abWindow::getTitle()
{
	return m_Title;
}
