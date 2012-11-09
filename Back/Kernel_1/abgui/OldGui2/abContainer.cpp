#include "abContainer.hpp"
#include <string.h>

using namespace abGui;


Container::Container() : Widget()
{
	m_WidgetList = new list<Widget>();
}

Container::~Container()
{

}


bool 
Container::addWidget(Widget *w)
{
	m_WidgetList->addNode(w);

	w->setContainer(m_Container);
	w->setSize(m_SizeX, m_SizeY);
	w->setPosition(0, 0);

	return true;
}


void
Container::Draw()
{
	Widget *w = m_WidgetList->getNode(0);

	while(w != NULL)
	{
		w->Draw();
		w = w->Next;
	}
}

