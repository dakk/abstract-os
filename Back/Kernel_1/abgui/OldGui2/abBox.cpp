#include "abBox.hpp"

using namespace abGui;

Box::Box(bool vert, bool expand, unsigned margin) : Container()
{
	m_VerticalBox = vert;
	m_Margin = margin;
	setExpand(expand);	
}


bool 
Box::addWidget(Widget *t)
{
	Widget *tmp;
	unsigned size;
	unsigned i;
	
	((Container *) this)->addWidget(t);

	/* Update size and position */
	i = 0;
	if(m_VerticalBox)
		size = m_SizeY / m_WidgetList->Len;
	else
		size = m_SizeX / m_WidgetList->Len;

	tmp = m_WidgetList->getNode(0);
	
	while(tmp != NULL)
	{
		if(m_VerticalBox)
		{
			tmp->setPosition(0, i * size);
			tmp->setSize(m_SizeX, size);
		}
		else
		{
			tmp->setPosition(i * size, 0);
			tmp->setSize(size, m_SizeY);
		}
	
		tmp = tmp->Next;
	}

	return true;
}


