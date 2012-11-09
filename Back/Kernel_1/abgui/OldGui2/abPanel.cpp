#include "abPanel.hpp"

using namespace abGui;

Panel::Panel(char *conf) : Widget()
{
	m_Applets = new list<PanelApplet>();

	if(conf == NULL)
	{
		defaultPopulate();
		m_Image = abGui->guiTheme->PanelImage;
	}

	m_Size = m_Image->SizeY;
	m_Expand = true;
	m_Position = POSITION_TOP;
}



Panel::~Panel()
{
	delete m_Applets;
}


void
Panel::Draw()
{
	unsigned i;
	unsigned pos = 2;
	unsigned rpos = 2;
	unsigned posy = (m_Image->SizeY - 8) / 2;
	PanelApplet *p = m_Applets->getNode(0);
	
	for(i = 0; i < abGui->SizeX; i++)
		abGui->drawImage(m_Image, i, 0);

	while(p != NULL)
	{
		if(p->AlignRight)
		{
			p->Draw(abGui->SizeX - rpos - p->Size, posy);
			rpos += p->Size;
		}
		else
		{
			p->Draw(pos, posy);
			pos += p->Size;
		}

		p = p->Next;
	}	
}


void 
Panel::defaultPopulate()
{
	addApplet(new AppletTask());
	addApplet(new AppletFPS(true));
	addApplet(new AppletBattery(true));
	addApplet(new AppletTime(true));
}


void 
Panel::setPosition(Position p)
{
	m_Position = p;  
}


Position 
Panel::getPosition()
{
	return m_Position;
}


void 
Panel::setExpand(bool exp)
{
	m_Expand = exp;	
}


bool 
Panel::getExpand()
{
	return m_Expand;
}


void 
Panel::setSize(unsigned size)
{
	m_Size = size;
}


unsigned 
Panel::getSize()
{
	return m_Size;
}


void
Panel::addApplet(PanelApplet *ap, bool align_right)
{
	if(ap == NULL)
		return;

	ap->setPanel(this);

	if(align_right)
		m_Applets->addEndNode(ap);
	else
		m_Applets->addNode(ap);
}

