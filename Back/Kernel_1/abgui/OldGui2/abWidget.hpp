#ifndef ABWIDGET_HPP
#define ABWIDGET_HPP

#include <Managers.hpp>

namespace abGui
{
	class Window;
	class Container;

	class Widget
	{
		public:
			Widget();
			~Widget();

			virtual void Draw() = 0;

			void setExpand(bool e);
			bool getExpand();

			void setSize(unsigned x, unsigned y);
			void setPosition(unsigned x, unsigned y);
			void setContainer(Container *w);
			unsigned getPosX();
			unsigned getPosY();

			Widget *Next;

		protected:
			unsigned m_PosX, m_PosY;
			unsigned m_SizeX, m_SizeY;

			abGuiManager *abGui;
			Container *m_Container;
			bool m_Expand;
	};
};

#endif
