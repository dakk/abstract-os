#ifndef ABWINDOW_HPP
#define ABWINDOW_HPP

#include "abWidget.hpp"
#include "abContainer.hpp"
#include <list.hpp>

using namespace abGui;

namespace abGui
{
	class Window : public Container
	{
		public:
			Window();
			~Window();

			void setTitle(char *title);
			char *getTitle();
			void Draw();

			unsigned getSizeX();
			unsigned getSizeY();
			void setSize(unsigned x, unsigned y);

			bool getDecorated();
			void setDecorated(bool dec);

			bool getResizable();
			void setResizable(bool res);

			void setPosition(unsigned x, unsigned y);
			unsigned getPositionX();
			unsigned getPositionY();

			void setFullscreen(bool f);
			bool getFullscreen();

			Window *Next;

		protected:
			char m_Title[128];
			bool m_Decorated;
			bool m_Resizable;
			bool m_Fullscreen;
			unsigned m_SizeX;
			unsigned m_SizeY;
			unsigned m_PosX;
			unsigned m_PosY;
	};

};

#endif
