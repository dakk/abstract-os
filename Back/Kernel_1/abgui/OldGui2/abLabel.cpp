#include "abLabel.hpp"

Label::Label(char *label) : Widget()
{
	strcpy(m_Label, label);
}

void
Label::Draw()
{
	abGui->drawText("ciao", 100, 100, 0x0);
	abGui->drawText(m_Label, m_Container->getPosX() + m_PosX, 
						m_Container->getPosY() + m_PosY, 0x0);
}
