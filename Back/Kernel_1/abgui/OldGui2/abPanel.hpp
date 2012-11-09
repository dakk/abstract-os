#ifndef ABPANEL_HPP
#define ABPANEL_HPP


#include <list.hpp>
#include <arch.h>
#include <stdio.h>
#include "abWidget.hpp"
#include "abImage.hpp"

namespace abGui
{
	typedef enum
	{
		POSITION_TOP,
		POSITION_BOTTOM,
		POSITION_RIGHT,
		POSITION_LEFT
	} Position;

	class Panel;

	/** Applet stub for the panel */
	class PanelApplet : public Widget
	{
		public:
			PanelApplet(bool ralign = false)
			{
				AlignRight = ralign;
			}

			void setPanel(Panel *p){ m_Panel = p; }

			virtual void Draw(unsigned x, unsigned y) = 0;
			virtual void Draw(){}

			PanelApplet *Next;
			bool AlignRight;
			unsigned Size;

		private:
			Panel *m_Panel;
	};

	
	class AppletTask : public PanelApplet
	{
		public:
			AppletTask(bool al = false) : PanelApplet(al)
			{
				Size = 1;
			}

			virtual void Draw(unsigned x, unsigned y)
			{

			}
	};


	/** Battery charge */
	class AppletBattery : public PanelApplet
	{
		public:
			AppletBattery(bool al = true) : PanelApplet(al)
			{
				Size = 10;
			}

			virtual void Draw(unsigned x, unsigned y)
			{
				abGui->drawRect(x, y - 3, x + 5, y + 10, 0x0, true);
			}
	};

	
	/** Renderized frame per second */
	class AppletFPS : public PanelApplet
	{
		public:
			AppletFPS(bool al = false) : PanelApplet(al)
			{
				m_Old = arch_get_clock_data()->seconds;
				m_New = arch_get_clock_data()->seconds;
				m_Frames = 0;	
				Size = 8 * 7;
			}

			virtual void Draw(unsigned x, unsigned y)
			{
				m_Frames++;

				m_New = arch_get_clock_data()->seconds;
				if(m_Old != m_New)
				{
					m_Old = m_New;
					strcpy(m_FPS, "FPS: ");
					strcat(m_FPS, itoa(m_Frames));
					m_Frames = 0;
				}
				
				abGui->drawText(m_FPS, x, y, 0x0);
			}
		
		private:
			char m_FPS[100];
			unsigned m_Old;
			unsigned m_New;
			unsigned m_Frames;
	};


	/** Time date */
	class AppletTime : public PanelApplet
	{
		public:
			AppletTime(bool al = true) : PanelApplet(al)
			{
				Size = 8 * 8;
			}
	
			virtual void Draw(unsigned x, unsigned y)
			{
				clock_data_t *c = arch_get_clock_data();
				char time[100];
				strcpy(time, itoa(c->hours));
				strcat(time, ":");
				strcat(time, itoa(c->minutes));
				strcat(time, ":");
				strcat(time, itoa(c->seconds));
				abGui->drawText(time, x, y, 0x0);
			}
	};



	class Panel : public Widget
	{
		public:
			Panel(char *conf = NULL);
			~Panel();

			void Draw();
	
			void setPanelImage(char *file);
			void setPanelImage(void *buf);

			void defaultPopulate();

			void setPosition(Position p);
			Position getPosition();

			void setExpand(bool exp);
			bool getExpand();

			void setSize(unsigned size);
			unsigned getSize();
	
			void addApplet(PanelApplet *ap, bool align_right = false);

		private:
			Image *m_Image;
			list<PanelApplet> *m_Applets;
			Position m_Position;
			unsigned m_Size;
			bool m_Expand;
	};
};


#endif
