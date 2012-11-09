#include "abWindow.hpp"
#include "abContainer.hpp"
#include <string.h>

using namespace abGui;


Window::Window() : Container()
{
	abGui->appendWindow(this);

	m_PosX = 100;
	m_PosY = 100;
	m_SizeX = 300;
	m_SizeY = 200;
	m_Decorated = true;
	m_Fullscreen = false;
	m_Container = this;
}

Window::~Window()
{

}



void
Window::Draw()
{
	if(m_Decorated)
	{
		abGui->drawGradientRect(m_PosX - 1, m_PosY - 15, m_PosX + m_SizeX + 1, m_PosY, 
						0x333333, 0x0A0A0A, false);
		abGui->drawRect(m_PosX - 1, m_PosY - 15, m_SizeX + m_PosX + 1, 
						m_SizeY + m_PosY + 1, 0x111111, false);
		abGui->drawLine(m_PosX, m_PosY - 1, m_SizeX + m_PosX, m_PosY - 1, 0x111111);	
		abGui->drawLine(m_PosX + m_SizeX - 15, m_PosY - 15, m_SizeX + m_PosX - 15, 
						m_PosY, 0x111111);
		abGui->drawText("x", m_PosX + m_SizeX - 10, m_PosY - 13, 0xFFFFFF);
		abGui->drawText(m_Title, m_PosX + 10, m_PosY - 12, 0xFFFFFF);
	}
	
	abGui->drawRect(m_PosX, m_PosY, m_SizeX + m_PosX, 
						m_SizeY + m_PosY, abGui->guiTheme->WindowBackgroundColor, true);
	

	Widget *w = m_WidgetList->getNode(0);
	while(w != NULL)
	{
		w->Draw();
		w = w->Next;
	}
	//((Container *) this)->Draw();
}

void 
Window::setTitle(char *title)
{
	strcpy(m_Title, title);
}


char *
Window::getTitle()
{
	return m_Title;
}


unsigned 
Window::getSizeX()
{
	return m_SizeX;
}


unsigned 
Window::getSizeY()
{
	return m_SizeY;
}



void 
Window::setSize(unsigned x, unsigned y)
{
	m_SizeX = x;
	m_SizeY = y;
}



bool 
Window::getDecorated()
{
	return m_Decorated;
}
	
	
void 
Window::setDecorated(bool dec)
{
	m_Decorated = dec;
}



bool 
Window::getResizable()
{
	return m_Resizable;
}
		
		
void 
Window::setResizable(bool res)
{
	m_Resizable = res;
}



void 
Window::setPosition(unsigned x, unsigned y)
{
	m_PosX = x;
	m_PosY = y;
}



unsigned 
Window::getPositionX()
{
	return m_PosX;
}
		
		
		
unsigned 
Window::getPositionY()
{
	return m_PosY;
}



void 
Window::setFullscreen(bool f)
{
	m_Fullscreen = f;
}


bool 
Window::getFullscreen()
{
	return m_Fullscreen;
}

