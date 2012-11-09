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
#include "AbGuiManager.hpp"
#include "abTheme.hpp"
#include "abMenu.hpp"
#include <Driver.hpp>
#include <arch.h>
#include <malloc.h>
#include <Managers.hpp>
#include <stdio.h>
#include <mm/mm.h>



#define ABDRAW_PIXEL(X, Y, CL)\
{ \
	register unsigned xy = ((X) * (m_Bpp >> 3)) + ((Y) * m_Bpsl); 	\
	m_RendBuf[xy] = (CL) & 0xFF;  	\
	m_RendBuf[xy+1] = ((CL) >> 8) & 0xFF; \
	m_RendBuf[xy+2] = ((CL) >> 16) & 0xFF; \
}


/**  */
AbGuiManager::AbGuiManager()
{
	m_WindowList = new list<abWindow>();
	m_ActiveWidget = NULL;
	m_ActiveWindow = NULL;
}



/** Destroy the gui */
AbGuiManager::~AbGuiManager()
{
	m_WindowList->Clear();
}


/** Gui mainloop */
void
AbGuiManager::mainLoop()
{
	/* Area to update */
	//unsigned upX0 = 0, upX1 = 0, upY0 = 0, upY1 = 0;
	bool exit = false;
	unsigned i;
	abWindow *w;
	bool first = true;
	VesaDriver::ModeInfo *vmi;


	m_Vesa = (VesaDriver *) Managers::Instance->deviceManager->getDevice("ve0")->getDriver();
	m_Mouse = (MouseDriver *) Managers::Instance->deviceManager->getDevice("ps0")->getDriver();

	if((m_Vesa == NULL))
		return;

	m_MouseX = m_Vesa->getX() / 2;
	m_MouseY = m_Vesa->getY() / 2;

	vmi = m_Vesa->getModeInfo();
	m_Bpp = vmi->bits_per_pixel;
	m_Bpsl = vmi->bytes_per_scan_line;

	m_RendDim = m_Vesa->getBpp() / 8 * m_Vesa->getX() * m_Vesa->getY();
	m_RendBuf = (char *) malloc(m_RendDim);

	m_Vesa->Memory = (char *) vmi->phys_base_ptr;


	/* Test */
	abMenu::MenuItem mi;
	//abProgressBar *pb;
	w = addWindow(" ");
	w->setDecorated(false);
	w->setSize(m_Vesa->getX(), 20);
	w->setPosition(0, 0);
	w->addWidget(new abLabel("Memory used: "), 0, 0);

	abLabel *lab2 = new abLabel("");
	w->addWidget(lab2, 100, 0);
	abLabel *lab = new abLabel("");
	w->addWidget(lab, w->DimX - 8 * 15, 0);
	w->addWidget(new abLabel("FPS"), w->DimX - 8 * 12, 0);

	w = addWindow("TestWindow!");
	w->setSize(290, 100);
	w->setPosition(200, 200);

	abMenu *menu = new abMenu();
	w->addWidget(menu, 0, 0);
	
	strcpy(mi.Label, "File");
	menu->addItem(0, mi);
	strcpy(mi.Label, "Modify");
	menu->addItem(0, mi);
	
	w->addWidget(new abButton("clickme"), 10, 25);
	w->addWidget(new abEntry(20), 70, 50);
	w->addWidget(new abLabel("Label: "), 10, 50);


	w = addWindow("TestWindow2!");
	w->setSize(200, 150);
	w->setPosition(500, 400);
	w->addWidget(new abButton("clickme"), 10, 10);
	w->addWidget(new abButton("clickme"), 90, 10);
	w->addWidget(new abButton("clickme"), 10, 50);

	w = addWindow("TextEntryWindow");
	w->setSize(200, 200);
	w->setPosition(20, 350);
	abTextEntry *te = new abTextEntry();
	te->setSize(180, 180);
	w->addWidget(te, 10, 10);
	

	unsigned old = arch_get_clock_data()->seconds;
	unsigned newo = arch_get_clock_data()->seconds;
	unsigned frames = 0;
	
	while(!exit)
	{		
		frames++;
		//pb->setPercentage((pb->getPercentage()+1) % 100);

		/* Clear */
		//clearBuffer();
		//clearBuffer(m_MouseX - 200, m_MouseY - 200, m_MouseX + 200, m_MouseY + 200);

		/* Check event */
		m_MouseX += m_Mouse->getX();
		m_MouseY += m_Mouse->getY();


		newo = arch_get_clock_data()->seconds;
		if(old != newo)
		{
			old = newo;
			lab->setText(itoa(frames));
			frames = 0;
		}

		lab2->setText(itoa(mm_get_used_mem()));

		/* If the left button of the mouse is clicked, change active window and active
		 * widget, if you click a button, call the callback registered for the button */
	
		if(m_Mouse->getClickedLt())
		{
			drawText("ciaoo", 100, 100, 0xFFF);
			w = m_WindowList->getNode(0);

			while(w != NULL)
			{
				if(	(m_MouseX > w->PosX) && (m_MouseX < w->PosX + w->DimX) &&
					(m_MouseY > w->PosY) && (m_MouseY < w->PosY + w->DimY) )
				{
					m_ActiveWindow = w;
					m_ActiveWidget = m_ActiveWindow->clickEvent(m_MouseX - w->PosX, m_MouseY - w->PosY, 1);
					
			drawText("caaaaiaoo", 100, 100, 0xFFF);

					char c = getchar();
					if(c != 0)
						m_ActiveWidget->keyEvent((uint32_t) c);
				}
				w = w->Next;
			}
		}

		/* Draw all */
		i = 0;
		w = m_WindowList->getNode(0);

		while(w != NULL)
		{
			w->Draw();

			w = w->Next;;
		}


		/* Draw cursor */
		drawBuffer((uint32_t *) abTheme::Pointer, m_MouseX, m_MouseY, 16, 16);

		/* Swap buffer */
		#if 01
    	  	while ((io_inb(0x3DA) & 0x08));
	      	while (!(io_inb(0x3DA) & 0x08));
		#endif
		swapBuffer();

		#if 0
		if(!first)
			swapBuffer();//*/swapBuffer(m_MouseX - 200, m_MouseY - 200, m_MouseX + 200, m_MouseY + 200);
		else
		{
			swapBuffer();
			first = false;
		}
		#endif
	}
}


/** Probe the gui */
bool 
AbGuiManager::Probe() 
{
	bool probe_state;

	VesaDriver *vd = new VesaDriver();
	probe_state = vd->Probe();
	delete(vd);

	return probe_state;
}




/**
 * Swap the buffer in the video ram 
 *
 * \param x0 start in x
 * \param x1 end in x
 * \param y0 start in y
 * \param y1 end in y
 */
void 
AbGuiManager::swapBuffer(unsigned x0, unsigned y0, unsigned x1, unsigned y1)
{
	register unsigned loc;

	if(x0 == x1)
		memcpy(m_Vesa->Memory, m_RendBuf, m_RendDim);
	else
	{
		for(; y0 < y1; y1--)
		{
			for(; x0 < x1; x1--)
			{
				loc = (y1 * m_Bpsl) + (x1 * (m_Bpp >> 3));
				m_Vesa->Memory[loc] = m_RendBuf[loc];
			}
		}
	}
}




void 
AbGuiManager::clearBuffer(unsigned x0, unsigned y0, unsigned x1, unsigned y1)
{
	if(x0 == x1)
		memset(m_RendBuf, 0, m_RendDim);
	else
	{
		register unsigned loc;


		for(;y0 < y1; y1--)
		{
			for(; x0 < x1; x1--)
			{
				loc = (y1 * m_Bpsl) + (x1 * (m_Bpp >> 3));
				m_RendBuf[loc] = 0;
			}
		}
	}
}




/** Draw a pixel */
void 
AbGuiManager::drawPixel(unsigned x, unsigned y, unsigned cl)
{		
	register unsigned xy = (x * (m_Bpp >> 3)) + (y * m_Bpsl);

	m_RendBuf[xy] = cl & 0xFF;
	m_RendBuf[xy+1] = (cl >> 8) & 0xFF;
	m_RendBuf[xy+2] = (cl >> 16) & 0xFF;
}

 

/** Draw a rect */
void 
AbGuiManager::drawRect(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned cl, bool fill)
{
	drawLine(x0, y0, x1, y0, cl);

	if(fill)
	{
		for(;y0 < y1; y1--)
			drawLine(x0, y1, x1, y1, cl);
	}
}




/** Draw a text string */
void 
AbGuiManager::drawText(char *data, unsigned x, unsigned y, unsigned cl, unsigned size)
{
	register char *let_data;
	register unsigned i, j;
	
	while(*data != '\0')
	{
		//if(size == 16) 
			let_data = (char *) abTheme::DefaultFont8x16[(unsigned) (*data)];
		//else if(size == 8) 
		//	let_data = (char *) abTheme::DefaultFont8x8[(unsigned) (*data)];

		for(i = 0; i < size; i++)
		{
			for(j = 0; j < 8; j++)
			{			
				if((let_data[i] & (1 << j)) != 0)
					ABDRAW_PIXEL((x + j), (y + i-4), ((uint32_t) cl));
			}
		}

		x += 8;
		data++;
	}
}



/** Draw a line */
void 
AbGuiManager::drawLine(unsigned x0, unsigned y0, unsigned x1, unsigned y1, unsigned cl)
{
	if(x0 == x1)
	{
		for(; y0 < y1; y0++)
			ABDRAW_PIXEL(x0, y0, cl);
	}
	else if(y1 == y0)
	{
		for(; x0 < x1; x0++)
			ABDRAW_PIXEL(x0, y0, cl);
	}
	else
	{
		register unsigned factor = (y1 - y0) / (x1 - x0);

		for(; x0 < x1; x0++, y0+=factor)
			ABDRAW_PIXEL(x0, y0, cl); 
	}
}




/** Draw a buffer */
void 
AbGuiManager::drawBuffer(uint32_t *data, unsigned x, unsigned y, unsigned dimx, unsigned dimy)
{
/*	register unsigned i, k;
	dimy--;
	for(i = 0; i < dimx; i++)
		for(; 0 < dimy; dimy--)
		{
			k = dimy * dimx + i;
			if(data[k] != ABGUI_TRASP)
				ABDRAW_PIXEL(x + i, y + dimy, data[k]);
		}
*/
	register unsigned i, j, k;

	for(i = 0; i < dimx; i++)
		for(j = 0; j < dimy; j++)
		{
			k = j * dimx + i;
			if(data[k] != ABGUI_TRASP)
				ABDRAW_PIXEL(x + i, y + j, data[k]);
		}
}




abWindow *
AbGuiManager::addWindow(char *name)
{
	abWindow *w = new abWindow(name);

	if(w == NULL)
		return NULL;

	m_WindowList->addNode(w);
	m_ActiveWindow = w;
	
	return w;
}
