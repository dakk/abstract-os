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
#include <ui/UiManager.hpp>
#include <ctype.h>
#include <config.h>
#include <Managers.hpp>
#include <Drivers/Vesa/Vesa.hpp>

UiManager::UiManager()
{
	m_WindowList = new list<Window>();
	m_RenderingDevice = NULL;
	m_WindowActive = NULL;
	m_Rendering = NULL;
}



UiManager::~UiManager()
{
	m_WindowList->Clear();
	delete m_WindowList;
}




/** Setup ui manager */
bool 
UiManager::Setup()
{
	m_RenderingDevice = Managers::Instance->deviceManager->getDevice("vesa0");

	if(m_RenderingDevice == NULL)
		return false;

	m_Rendering = new Rendering(m_RenderingDevice);

	return true;
}



/** Return the rendering engine */
Rendering *
UiManager::getRenderingEngine()
{
	return m_Rendering;
}



/** Add a window to the manager */
bool 
UiManager::addWindow(Window *w)
{
	if(w != NULL)
		m_WindowList->addNode(w);
	else
		return false;

	return true;
}


#include <ui/widgets/Label.hpp>
#include <ui/widgets/Button.hpp>

/** Main rendering loop */
void
UiManager::mainLoop()
{
	Window *w = new Window();
	w->setPosition(100, 100);
	w->Resize(300, 200);

	Button *l = new Button("Ciao");
	w->setWidget(l);

	addWindow(w);

	m_Rendering->drawRectGradient(0, 0, 800, 600, 0x0000AA, 0x0000EE);

	while(1)
	{
		Window *w = m_WindowList->getNode(0);

		while(w != NULL)
		{
			if(w != m_WindowActive)
				w->Draw(255);
			w = w->Next;
		}

		//if(m_WindowActive != NULL)
		//	m_WindowActive->Draw();


		m_Rendering->swapBuffer();
	}
}

