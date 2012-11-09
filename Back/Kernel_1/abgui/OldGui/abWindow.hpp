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
#ifndef ABWINDOW_HPP
#define ABWINDOW_HPP

#include "abWidget.hpp"
#include "abButton.hpp"
#include "abEntry.hpp"
#include "abLabel.hpp"
#include "abMenu.hpp"
#include "abProgressBar.hpp"
#include "abTextEntry.hpp"
#include <list.hpp>

class AbGuiManager;

class abWindow
{
	public:
		static const unsigned START_POS_X	=	10;
		static const unsigned START_POS_Y	=	10;
		static const unsigned START_DIM_X	=	100;
		static const unsigned START_DIM_Y	=	100;

		abWindow(char *name);
		~abWindow();
		void Draw();
		void setSize(unsigned x, unsigned y);
		void setPosition(unsigned x, unsigned y);
		void setTitle(char *name);
		char *getTitle();
		void setDecorated(bool state);
		bool getDecorated();

		virtual void closeCallback(){}

		void addWidget(abWidget *w, unsigned x, unsigned y);

		abWidget *clickEvent(unsigned x, unsigned y, unsigned key);

		abWindow *Next;
		bool m_NeedUpdate;


		unsigned DimX;
		unsigned DimY;
		unsigned PosX;
		unsigned PosY;

	private:
		bool m_isDecorated;				///
		char m_Title[512];


	protected:
		AbGuiManager *m_GuiEnv;
		list<abWidget> *m_WidgetList;

};

#endif
