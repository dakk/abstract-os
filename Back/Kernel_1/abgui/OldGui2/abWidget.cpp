#include "abWidget.hpp"
#include "abContainer.hpp"

using namespace abGui;

Widget::Widget()
{
	abGui = Managers::Instance->guiManager;
	m_Container = NULL;
}

Widget::~Widget()
{

}

void
Widget::setContainer(Container *w)
{
	m_Container = w;
}

void
Widget::setSize(unsigned x, unsigned y)
{
	m_SizeX = x;
	m_SizeY = y;
}


void
Widget::setPosition(unsigned x, unsigned y)
{
	m_PosX = x;
	m_PosY = y;
}

void 
Widget::setExpand(bool e)
{
	m_Expand = e;
}


bool
Widget::getExpand()
{
	return m_Expand;
}

unsigned
Widget::getPosX()
{
	return m_PosX;
}

unsigned 
Widget::getPosY()
{
	return m_PosY;
}

